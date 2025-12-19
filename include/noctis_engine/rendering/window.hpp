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

    bool should_close() const { return glfwWindowShouldClose(m_glfwWindow); }
    void poll_events() const { glfwPollEvents(); }
    void swap_buffers() const { glfwSwapBuffers(m_glfwWindow); }
    double get_time() const { return glfwGetTime(); }

private:
    GLFWwindow *m_glfwWindow = nullptr;

    static void GLFWErrorCallback(int code, const char *desc);
};

NCENG_API Window create_context(int windowWidth, int windowHeight, const std::string &title);

} // namespace NoctisEngine
