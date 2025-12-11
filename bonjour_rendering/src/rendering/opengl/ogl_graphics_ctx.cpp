#include "bjr/rendering/opengl/ogl_graphics_ctx.hpp"

namespace Bjr
{
    
std::shared_ptr<OpenGLCtx> OpenGLCtx::create() {
    return std::shared_ptr<OpenGLCtx>(new OpenGLCtx());
}

} // namespace Bjr

