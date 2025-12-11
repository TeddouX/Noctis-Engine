#include "bjr/window.hpp"
#include <print>

namespace Bjr
{

Window::Window(int width, int height, const std::string &title, std::shared_ptr<GraphicsCtx> ctx)
    : m_graphicsCtx(ctx)
{
    glfwSetErrorCallback(Window::GLFWErrorCallback);
    glfwInit();

    if (ctx->getBackend() == GraphicsBackend::OPENGL) {
        // Opengl 4.6
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!m_glfwWindow) {
        std::println("Failed to create a window.");
        glfwTerminate();
        return;
    }

    glfwSetWindowUserPointer(m_glfwWindow, this);
    glfwMakeContextCurrent(m_glfwWindow);
}

void Window::GLFWErrorCallback(int code, const char *desc) {
    std::println("glfw error: {}", desc);
}

} // namespace Bjr
