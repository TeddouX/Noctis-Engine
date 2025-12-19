#include <rendering/shader.hpp>

#include <rendering/opengl/ogl_shader.hpp>
#include <rendering/render_state.hpp>

namespace NoctisEngine
{
    
std::unique_ptr<Shader> Shader::Create(
    const char *vertCode, 
    const char *fragCode
) {
    switch (RenderState::get_backend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<ShaderOpenGL>(vertCode, fragCode);
        default: return nullptr;
    }
}
    
} // namespace NoctisEngine
