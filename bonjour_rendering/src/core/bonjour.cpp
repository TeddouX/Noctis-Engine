#include <core/bonjour.hpp>
#include <core/window.hpp>
#include <rendering/opengl/ogl_handler.hpp>

#include <GLFW/glfw3.h>

#include <print>

namespace Bjr
{

Err init(GraphicsBackend backend) {
    if (!Internal::state.hasContext)
        return Err("Please create a context before initializing.");

    Internal::state.backend = backend;
    Internal::state.initialized = true;

    if (backend == GraphicsBackend::OPENGL) {
        auto ogl = std::make_shared<Internal::OpenGLHandler>();
        ogl->init();
        
        Internal::state.handler = ogl;
    }

    return Bjr::noerr;
}

} // namespace Bjr
