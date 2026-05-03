#include <rendering/renderer.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <rendering/mesh/mesh_view.hpp>
#include <ecs/component/transform.hpp>
#include <rendering/buffer_utils.hpp>
#include <rendering/shader_bindings.hpp>
#include <core/exception.hpp>

namespace NoctisEngine
{
   
static auto glad_enable_disable(bool b, GLenum name) -> void {
    if (b) glEnable(name);
    else   glDisable(name);
}

Renderer::Renderer(std::shared_ptr<MeshManager> meshManager) 
    : meshManager_(meshManager) 
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback((GLDEBUGPROC)OpenGLDbgMessCallback, this);

    commandBuf_ = GPUBuffer(1, "renderer_command_buffer");
    objectsSSBO_ = GPUBuffer(1, "renderer_object_buffer");
}

auto Renderer::set_backface_culling(bool b) const -> void {
    glad_enable_disable(b, GL_CULL_FACE);
}

auto Renderer::set_depth_testing(bool b) const -> void {
    glad_enable_disable(b, GL_DEPTH_TEST);
}

auto Renderer::set_clear_screen_color(Color col) -> void {
    glClearColor(
        col.red_f(), 
        col.green_f(), 
        col.blue_f(), 
        col.alpha_f()
    );
}

auto Renderer::set_throw_on_err(bool b) -> void {
    throwOnErr_ = b;
}

void Renderer::clear_screen() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto Renderer::set_viewport_size(int w, int h) -> void {
    glViewport(0, 0, w, h);
}

auto Renderer::set_blend(bool b) -> void {
    glad_enable_disable(b, GL_BLEND);
}

auto Renderer::set_blend_func(BlendFunc sFactor, BlendFunc dFactor) -> void {
    glBlendFunc(static_cast<GLenum>(sFactor), static_cast<GLenum>(dFactor));
}

auto Renderer::render_entities(entt::registry &reg) -> void {
    auto view = reg.view<
        const Transform, 
        const MeshView, 
        const MaterialKey
    >(entt::exclude_t<InstanceRenderedGroup>());

    std::vector<DrawElementsIndirectCommand> commands;
    std::vector<ObjectData> objects;

    for (const auto &[entity, transform, mv, matKey] : view.each()) {
        commands.push_back(DrawElementsIndirectCommand{
            .count         = static_cast<GLuint>(mv.indicesCount),
            .instanceCount = 1u,
            .firstIndex    = static_cast<GLuint>(mv.indicesOffset),
            .baseVertex    = static_cast<GLint>(mv.verticesOffset),
            .baseInstance  = static_cast<GLuint>(objects.size()),
        });

        objects.push_back(ObjectData{
            .modelMat    = transform.model_matrix(),
            .materialIdx = static_cast<GLuint>(matKey),
        });
    }

    // Instanced rendered entities
    if (!irEntities_.empty()) {
        if (irEntities_.size() != irgMeshViews_.size())
            throw Exception("There isn't a mesh view set for every IRG. Make sure to call Renderer::set_irg_mesh_view for every IRG.");

        std::vector<DrawElementsIndirectCommand> irCommands;
        for (auto &meshView : irgMeshViews_) {
            irCommands.push_back(DrawElementsIndirectCommand{
                .count         = static_cast<GLuint>(meshView.indicesCount),
                .instanceCount = 0u,
                .firstIndex    = static_cast<GLuint>(meshView.indicesOffset),
                .baseVertex    = static_cast<GLint>(meshView.verticesOffset),
                .baseInstance  = 0, 
            });
        }

        auto group = reg.group(
            entt::get_t<
                Transform, 
                MeshView, 
                MaterialKey, 
                InstanceRenderedGroup
            >(), 
            entt::exclude_t<>()
        );

        auto idx = 0;
        for (auto &entities : irEntities_) {
            irCommands[idx].baseInstance = objects.size();

            for (auto &entity : entities) {
                const auto &[transform, sprite, matKey] = group.get<Transform, MeshView, MaterialKey>(entity);

                irCommands[idx].instanceCount++;
                objects.push_back(ObjectData{
                    .modelMat    = transform.model_matrix(),
                    .materialIdx = static_cast<GLuint>(matKey),
                });
            }

            idx++;
        }

        commands.insert_range(commands.end(), irCommands);
    }

    resize_buffer(commandBuf_, commands);
    resize_buffer(objectsSSBO_, objects);

    // TODO: Map them and write to them using a pointer
    commandBuf_.write(get_cpu_buffer_view(commands, 0, commands.size()), 0);
    objectsSSBO_.write(get_cpu_buffer_view(objects, 0, objects.size()), 0);
    objectsSSBO_.bind_buffer_base(BufferType::SHADER_STORAGE_BUFFER, ShaderBindings::OBJECTS_BUFFER_SSBO);

    meshManager_->bind();

    commandBuf_.bind_as(BufferType::DRAW_INDIRECT_BUFFER);

    glMultiDrawElementsIndirect(
        GL_TRIANGLES,
        GL_UNSIGNED_INT,
        (void*)0,
        commands.size(),
        0
    ); 
}

auto Renderer::create_irg() -> InstanceRenderedGroup {
    return InstanceRenderedGroup{numInstanceRenderedGroups_++};
}

auto Renderer::set_irg_mesh_view(InstanceRenderedGroup group, MeshView mesh) -> void {
    if (group.get() >= irgMeshViews_.size())
        irgMeshViews_.resize(group.get() + 1);
    irgMeshViews_[group.get()] = mesh;
}

auto Renderer::register_ir_entity(const Entity &entity) -> void {
    const auto *irg = entity.try_get_component<InstanceRenderedGroup>();
    if (irg == nullptr) {
        Log::Warn("Called Renderer::register_ir_entity with an entity that doesn't have an to an InstanceRenderedGroup");
        return;
    }

    if (!irg->is_valid()) {
        Log::Error("Tried to call Renderer::register_ir_entity with an entity that has and invalid IRG");
        return;
    }

    auto idx = irg->get();
    if (idx >= irEntities_.size())
        irEntities_.resize(idx + 1);

    irEntities_[idx].push_back(entity.get_raw());
}


void Renderer::OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam
) {
    if (severity == GL_DEBUG_SEVERITY_LOW)
        Log::Info("OpenGL: {}", message);
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
        Log::Warn("OpenGL: {}", message);
        Log::Warn("Stacktrace:\n{}", std::stacktrace::current(1));
    }
    else if (severity == GL_DEBUG_SEVERITY_HIGH) {
        auto gh = static_cast<const Renderer *>(userParam);

        if (gh->throwOnErr_) {
            Log::Error("OpenGL Error: {}", message);
            throw Exception("An OpenGL error has been generated and throw on error is enabled, for more info see above.");
        }
        else {
            Log::Error("OpenGL: {}", message);
            Log::Error("Stacktrace:\n{}", std::stacktrace::current(1));
        }
    }
}

} // namespace NoctisEngine
