#include <rendering/render_state.hpp>

#include <rendering/opengl/ogl_handler.hpp>

namespace NoctisEngine
{
    
auto RenderState::init(GraphicsBackend backend) -> std::shared_ptr<GraphicsHandler> {
    std::shared_ptr<GraphicsHandler> createdHandler;
    switch (backend) {
        case GraphicsBackend::OPENGL:
            createdHandler = std::make_shared<OpenGLHandler>();
            break;

        default:
            break;
    }

    handler_ = createdHandler;
    return handler_;
}

} // namespace NoctisEngine

