#include <bjr/rendering/opengl/ogl_graphics_ctx.hpp>
#include <bjr/window.hpp>

#include <print>

int main() {
    auto ctx = Bjr::OpenGLCtx::create();

    Bjr::Window window(800, 600, "Testing", ctx);

    while (!window.shouldClose()) {
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}