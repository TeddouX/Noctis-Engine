#include <rendering/graphics_handler.hpp>

#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <rendering/render_state.hpp>
#include <core/logging.hpp>

namespace NoctisEngine
{

static auto glad_enable_disable(bool b, GLenum name) -> void {
    if (b) glEnable(name);
    else   glDisable(name);
}

GraphicsHandler::GraphicsHandler() {
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

auto GraphicsHandler::set_backface_culling(bool b) const -> void {
    glad_enable_disable(b, GL_CULL_FACE);
}

auto GraphicsHandler::set_depth_testing(bool b) const -> void {
    glad_enable_disable(b, GL_DEPTH_TEST);
}

void GraphicsHandler::clear_screen() const {
    const Color &color = RenderState::clear_screen_color();

    glClearColor(
        color.red_f(), 
        color.green_f(), 
        color.blue_f(), 
        color.alpha_f()
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsHandler::OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam
) {
    if (severity == GL_DEBUG_SEVERITY_LOW)
        Log::Info("OpenGL: {}", message);
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM)
        Log::Warn("OpenGL: {}", message);
    else if (severity == GL_DEBUG_SEVERITY_HIGH)
        Log::Error("OpenGL: {}", message);
}

} // namespace NoctisEngine
