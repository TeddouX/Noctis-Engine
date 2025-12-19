#include <rendering/ssbo.hpp>

#include <rendering/opengl/ogl_ssbo.hpp>
#include <rendering/render_state.hpp>

namespace NoctisEngine
{
    
std::unique_ptr<SSBO> SSBO::Create(int bindPoint) {
    switch (RenderState::get_backend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<SSBOOpenGL>(bindPoint);
        default: return nullptr;
    }
}
    
} // namespace NoctisEngine
