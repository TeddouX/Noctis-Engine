#include <rendering/command_buffer.hpp>

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

CommandBuffer::CommandBuffer() {
    buf_ = GPUBuffer(sizeof(DrawElementsIndirectCommand), "command_buffer");
}

auto CommandBuffer::build(const entt::registry &reg) -> std::uint32_t {
    auto view = reg.view<const MeshView>();
    
    std::vector<DrawElementsIndirectCommand> commands;
    commands.reserve(view.size());

    GLint base{};
    for (const auto &[entity, meshView] : view.each()) {
        commands.push_back(DrawElementsIndirectCommand{
            .count         = static_cast<GLuint>(meshView.indicesCount),
            .instanceCount = 1u,
            .firstIndex    = static_cast<GLuint>(meshView.indicesOffset),
            .baseVertex    = base,
            .baseInstance  = 0, 
        });

        base += meshView.verticesCount;
    }

    resize_buffer(buf_, commands, "command_buffer");
    buf_.write(get_cpu_buffer_view(commands, 0, commands.size()), 0);

    return commands.size();
}

auto CommandBuffer::bind() -> void {
    buf_.bind_as(BufferType::DRAW_INDIRECT_BUFFER);
}

} // namespace NoctisEngine
