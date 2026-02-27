#include <rendering/renderer3D.hpp>

#include <glad/gl.h>

#include <rendering/shader_bindings.hpp>
#include <rendering/buffer_utils.hpp>
#include <ecs/component/transform.hpp>

namespace NoctisEngine
{
    
Renderer3D::Renderer3D(std::shared_ptr<MeshManager> meshManager) {
    init(meshManager);
}

auto Renderer3D::render_entities(entt::registry &reg) -> void {
    auto view = reg.view<const Transform, const MeshView, const MaterialKey>();

    std::vector<DrawElementsIndirectCommand> commands;
    std::vector<ObjectData> objects;

    for (const auto &[entity, transform, meshView, matKey] : view.each()) {
        commands.push_back(DrawElementsIndirectCommand{
            .count         = static_cast<GLuint>(meshView.indicesCount),
            .instanceCount = 1u,
            .firstIndex    = static_cast<GLuint>(meshView.indicesOffset),
            .baseVertex    = static_cast<GLint>(meshView.verticesOffset),
            .baseInstance  = 0, 
        });

        objects.push_back(ObjectData{
            .modelMat = transform.model_matrix(),
            .materialIdx = static_cast<GLuint>(matKey),
        });
    }

    resize_buffer(commandBuf_, commands);
    resize_buffer(objectsSSBO_, objects);

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

} // namespace NoctisEngine
