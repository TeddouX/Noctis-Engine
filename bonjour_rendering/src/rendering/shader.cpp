#include <rendering/shader.hpp>
#include <rendering/opengl/ogl_shader.hpp>
#include <core/bonjour.hpp>

namespace Bjr
{
    
std::unique_ptr<Shader> Shader::Create(
    const char *vertCode, 
    const char *fragCode
) {
    switch (Bjr::getBackend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<ShaderOpenGL>(vertCode, fragCode);
        default: return nullptr;
    }
}
    
} // namespace Bjr
