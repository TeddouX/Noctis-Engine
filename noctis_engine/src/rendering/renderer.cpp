#include <rendering/renderer.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <rendering/mesh/mesh_view.hpp>
#include <ecs/component/transform.hpp>
#include <rendering/buffer_utils.hpp>
#include <rendering/shader_bindings.hpp>

namespace NoctisEngine
{
   
static auto glad_enable_disable(bool b, GLenum name) -> void {
    if (b) glEnable(name);
    else   glDisable(name);
}

auto Renderer::set_backface_culling(bool b) const -> void {
    glad_enable_disable(b, GL_CULL_FACE);
}

auto Renderer::set_depth_testing(bool b) const -> void {
    glad_enable_disable(b, GL_DEPTH_TEST);
}

auto Renderer::set_clear_screen_color(Color col) -> void {
    clearScrCol_ = col;
}

auto Renderer::set_throw_on_err(bool b) -> void {
    throwOnErr_ = b;
}

void Renderer::clear_screen() const {
    glClearColor(
        clearScrCol_.red_f(), 
        clearScrCol_.green_f(), 
        clearScrCol_.blue_f(), 
        clearScrCol_.alpha_f()
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto Renderer::set_viewport_size(int w, int h) -> void {
    glViewport(0, 0, w, h);
}

auto Renderer::init(std::shared_ptr<MeshManager> meshManager) -> void {
    meshManager_ = meshManager;

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback((GLDEBUGPROC)OpenGLDbgMessCallback, this);

    commandBuf_ = GPUBuffer(1, "renderer_command_buffer");
    objectsSSBO_ = GPUBuffer(1, "renderer_object_buffer");
}

void Renderer::OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam
) {
    if (severity == GL_DEBUG_SEVERITY_LOW)
        Log::Info("OpenGL: {}", message);
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
        Log::Warn("OpenGL: {}", message);
        Log::Warn("Stacktrace:\n{}", std::stacktrace::current(1));
    }
    else if (severity == GL_DEBUG_SEVERITY_HIGH) {
        auto gh = static_cast<const Renderer *>(userParam);

        if (gh->throwOnErr_) {
            Log::Error("OpenGL Error: {}", message);
            throw Exception("An OpenGL error has been generated and throw on error is enabled, for more info see above.");
        }
        else {
            Log::Error("OpenGL: {}", message);
            Log::Error("Stacktrace:\n{}", std::stacktrace::current(1));
        }
    }
}

} // namespace NoctisEngine
