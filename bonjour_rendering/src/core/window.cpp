#include <core/window.hpp>
#include <core/bonjour.hpp>

#include <print>

namespace Bjr
{

Window::Window(int width, int height, const std::string &title) {
    glfwInit();
    glfwSetErrorCallback(Window::GLFWErrorCallback);

    if (Bjr::getBackend() == GraphicsBackend::OPENGL) {
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
        exit(-1);
    }

    glfwSetWindowUserPointer(m_glfwWindow, this);
    glfwMakeContextCurrent(m_glfwWindow);
}

void Window::GLFWErrorCallback(int code, const char *desc) {
    std::println("glfw error: {}", desc);
}

Window createContext(int windowWidth, int windowHeight, const std::string &title) {
    Window window{windowWidth, windowHeight, title};
    Internal::state.hasContext = true;
    return window;
}

} // namespace Bjr
