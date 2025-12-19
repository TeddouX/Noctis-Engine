#include <rendering/uniform_buffer.hpp>

#include <rendering/opengl/ogl_uniform_buffer.hpp>
#include <rendering/render_state.hpp>

namespace NoctisEngine
{
    
std::unique_ptr<UniformBuffer> UniformBuffer::Create(int bindPoint) {
    switch (RenderState::get_backend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<UniformBufferOpenGL>(bindPoint);
        default: return nullptr;
    }
}

} // namespace NoctisEngine
