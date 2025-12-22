#include <rendering/render_state.hpp>

namespace NoctisEngine
{
    
auto RenderState::init() -> std::shared_ptr<GraphicsHandler> {
    handler_ = std::make_shared<GraphicsHandler>();
    return handler_;
}

} // namespace NoctisEngine

