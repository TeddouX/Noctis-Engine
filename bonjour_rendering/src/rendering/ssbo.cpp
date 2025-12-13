#include <rendering/ssbo.hpp>
#include <rendering/opengl/ogl_ssbo.hpp>
#include <core/bonjour.hpp>

namespace Bjr
{
    
std::unique_ptr<SSBO> SSBO::Create(int bindPoint) {
    switch (Bjr::getBackend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<SSBOOpenGL>(bindPoint);
        default: return nullptr;
    }
}
    
} // namespace Bjr
