#include <rendering/opengl/ogl_handler.hpp>
#include <core/bonjour.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <print>

namespace Bjr::Internal
{

void OpenGLHandler::init() {
    if (!gladLoadGL()) {
        std::println("Failed to load OpenGL functions.");
        glfwTerminate();
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback(OpenGLDbgMessCallback, nullptr);
}

void OpenGLHandler::clearScreen() {
    const Color &color = Internal::state.clearScreenColor;

    glClearColor(
        color.redFloat(), 
        color.greenFloat(), 
        color.blueFloat(), 
        color.alphaFloat()
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLHandler::OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam
) {
    if (severity == GL_DEBUG_SEVERITY_LOW)
        std::println("OGL Info: {}", message);
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM)
        std::println("OGL Warn: {}", message);
    else if (severity == GL_DEBUG_SEVERITY_HIGH)
        std::println("OGL Error: {}", message);
}

} // namespace Bjr::Internal
