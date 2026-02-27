#include <rendering/window/window.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <print>

#include <input/input_system.hpp>
#include <core/logging.hpp>
#include <core/exception.hpp>

namespace NoctisEngine
{

static auto get_window_ptr(GLFWwindow *glfwWindow) -> Window * {
    return static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
}

Window::Window(int width, int height, const std::string &title) 
    : deltaTime_(0.0), lastFrame_(0.0)
{
    glfwInit();
    glfwSetErrorCallback(Window::GLFWErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    
    m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!m_glfwWindow)
        throw Exception("Failed to create a window.");

    glfwSetKeyCallback(m_glfwWindow, InputSystem::GLFWKeyCallback);
    glfwSetMouseButtonCallback(m_glfwWindow, InputSystem::GLFWMouseButtonCallback);
    glfwSetCursorPosCallback(m_glfwWindow, InputSystem::GLFWCursorPosCallback);
    glfwSetWindowCloseCallback(m_glfwWindow, Window::GLFWWindowCloseCallback);
    glfwSetWindowSizeCallback(m_glfwWindow, Window::GLFWWindowResizeCallback);

    glfwSetWindowUserPointer(m_glfwWindow, this);
    glfwMakeContextCurrent(m_glfwWindow);

    if (!gladLoadGL(glfwGetProcAddress))
        throw Exception("Failed to load OpenGL functions.");
}

auto Window::should_close() const -> bool {
    return glfwWindowShouldClose(m_glfwWindow); 
}

auto Window::set_should_close(bool b) const -> void {
    glfwSetWindowShouldClose(m_glfwWindow, b); 
}

auto Window::swap_buffers() const -> void {
    glfwSwapBuffers(m_glfwWindow); 
}

auto Window::get_time() const -> double {
    return glfwGetTime(); 
}

auto Window::lock_cursor() const -> void {
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
}

auto Window::unlock_cursor() const -> void {
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
}

auto Window::delta_time() const -> double {
    return deltaTime_; 
}

auto Window::set_title(const std::string &newTitle) const -> void {
    glfwSetWindowTitle(m_glfwWindow, newTitle.c_str()); 
}

auto Window::get_events() -> std::queue<WindowEvent> & {
    return events_;
}

auto Window::poll_events() -> void {
    // Set released keys to up
    InputSystem::update();
    
    glfwPollEvents();

    double currentFrame = glfwGetTime();
	deltaTime_ = currentFrame - lastFrame_;
	lastFrame_ = currentFrame;
}

void Window::GLFWErrorCallback(int code, const char *desc) {
    Log::Error("GLFW error: {}", desc);
}

auto Window::GLFWWindowCloseCallback(GLFWwindow *glfwWindow) -> void {
    Window *window = get_window_ptr(glfwWindow);

    window->events_.push(WindowEvent{
        .type = WindowEvent::Type::CLOSE,
        .data = {}
    });
}

auto Window::GLFWWindowResizeCallback(GLFWwindow *glfwWindow, int width, int height) -> void {
    Window *window = get_window_ptr(glfwWindow);

    window->events_.push(WindowEvent{
        .type = WindowEvent::Type::RESIZE,
        .data = WE_ResizeData{
            .newWidth = width, 
            .newHeight = height
        }
    });
}

} // namespace NoctisEngine
