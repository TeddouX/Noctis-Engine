#pragma once
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

#include "rendering/graphics_ctx.hpp"

namespace Bjr
{
    
class Window {
public:
    Window(int width, int height, const std::string &title, std::shared_ptr<GraphicsCtx> ctx);

    bool shouldClose() const { return glfwWindowShouldClose(m_glfwWindow); }
    void pollEvents() const { glfwPollEvents(); }
    void swapBuffers() const { glfwSwapBuffers(m_glfwWindow); }

private:
    GLFWwindow *m_glfwWindow = nullptr;
    std::shared_ptr<GraphicsCtx> m_graphicsCtx;

    static void GLFWErrorCallback(int code, const char *desc);
};

} // namespace Bjr
