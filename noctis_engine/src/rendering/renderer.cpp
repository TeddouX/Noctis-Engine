#include <rendering/renderer.hpp>

#include <rendering/mesh_view.hpp>
#include <ecs/component/transform.hpp>

#include <glad/glad.h>

namespace NoctisEngine
{
    
struct DrawElementsIndirectCommand {
    GLuint count;
    GLuint instanceCount;
    GLuint firstIndex;
    GLint  baseVertex;
    GLuint baseInstance;
};

Renderer::Renderer(std::shared_ptr<MeshManager> meshManager)
    : meshManager_(meshManager)
{
    commandBuf_ = GPUBuffer(sizeof(DrawElementsIndirectCommand), "renderer_command_buffer");
    modelMatSSBO_ = GPUBuffer(sizeof(glm::mat4), "renderer_matrices_buffer");
}

auto Renderer::render(entt::registry &reg) -> void {
    auto view = reg.view<const Transform, const MeshView>();

    std::vector<DrawElementsIndirectCommand> commands;
    std::vector<glm::mat4> matrices;

    for (const auto &[entity, transform, meshView] : view.each()) {
        commands.push_back(DrawElementsIndirectCommand{
            .count         = static_cast<GLuint>(meshView.indicesCount),
            .instanceCount = 1u,
            .firstIndex    = static_cast<GLuint>(meshView.indicesOffset),
            .baseVertex    = static_cast<GLint>(meshView.verticesOffset),
            .baseInstance  = 0, 
        });

        matrices.push_back(transform.model_matrix());
    }

    resize_buffer(commandBuf_, commands, "renderer_command_buffer");
    resize_buffer(modelMatSSBO_, matrices, "renderer_matrices_buffer");

    commandBuf_.write(get_cpu_buffer_view(commands, 0, commands.size()), 0);
    modelMatSSBO_.write(get_cpu_buffer_view(matrices, 0, matrices.size()), 0);
    modelMatSSBO_.bind_buffer_base(BufferType::SHADER_STORAGE_BUFFER, 1);

    meshManager_->bind();

    commandBuf_.bind_as(BufferType::DRAW_INDIRECT_BUFFER);

    glMultiDrawElementsIndirect(
        GL_TRIANGLES,
        GL_UNSIGNED_INT,
        nullptr,
        commands.size(),
        0
    );
}

} // namespace NoctisEngine
