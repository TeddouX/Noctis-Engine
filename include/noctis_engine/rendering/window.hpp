#pragma once
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

#include "../noctis_engine.hpp"

namespace NoctisEngine
{

class NCENG_API Window {
public:
    Window(int width, int height, const std::string &title);

    auto should_close() const -> bool { return glfwWindowShouldClose(m_glfwWindow); }
    auto set_should_close(bool b) const -> void { glfwSetWindowShouldClose(m_glfwWindow, b); }

    auto poll_events() const -> void;

    auto swap_buffers() const -> void { glfwSwapBuffers(m_glfwWindow); }

    auto get_time() const -> double { return glfwGetTime(); }

    auto lock_cursor() const -> void { glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
    auto unlock_cursor() const -> void { glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

private:
    GLFWwindow *m_glfwWindow = nullptr;

    static void GLFWErrorCallback(int code, const char *desc);
};

NCENG_API Window create_context(int windowWidth, int windowHeight, const std::string &title);

} // namespace NoctisEngine
