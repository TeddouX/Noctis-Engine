#pragma once
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

namespace Bjr
{

class Window {
public:
    Window(int width, int height, const std::string &title);

    bool shouldClose() const { return glfwWindowShouldClose(m_glfwWindow); }
    void pollEvents() const { glfwPollEvents(); }
    void swapBuffers() const { glfwSwapBuffers(m_glfwWindow); }
    double getTime() const { return glfwGetTime(); }

private:
    GLFWwindow *m_glfwWindow = nullptr;

    static void GLFWErrorCallback(int code, const char *desc);
};

Window createContext(int windowWidth, int windowHeight, const std::string &title);

} // namespace Bjr
