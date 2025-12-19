#include <rendering/window.hpp>

#include <print>

#include <rendering/render_state.hpp>

namespace NoctisEngine
{

Window::Window(int width, int height, const std::string &title) {
    glfwInit();
    glfwSetErrorCallback(Window::GLFWErrorCallback);

    if (RenderState::get_backend() == GraphicsBackend::OPENGL) {
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

NCENG_API Window create_context(int windowWidth, int windowHeight, const std::string &title) {
    Window window{windowWidth, windowHeight, title};
    
    RenderState::context_created();

    return window;
}

} // namespace NoctisEngine
