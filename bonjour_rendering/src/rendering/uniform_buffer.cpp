#include <rendering/uniform_buffer.hpp>
#include <rendering/opengl/ogl_uniform_buffer.hpp>
#include <core/bonjour.hpp>

namespace Bjr
{
    
std::unique_ptr<UniformBuffer> UniformBuffer::Create(int bindPoint) {
    switch (Bjr::getBackend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<UniformBufferOpenGL>(bindPoint);
        default: return nullptr;
    }
}

} // namespace Bjr
