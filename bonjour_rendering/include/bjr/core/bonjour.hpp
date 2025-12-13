#pragma once
#include "../rendering/handler.hpp"
#include "../math/color.hpp"
#include "error.hpp"

#include <memory>
#include <string>

namespace Bjr
{

enum class GraphicsBackend {
    OPENGL,
    // TODO
    VULKAN
};

namespace Internal
{

inline struct BjrState {
    bool hasContext = false;
    bool initialized = false;
    std::shared_ptr<Internal::GraphicsHandler> handler;
    GraphicsBackend backend;
    Color clearScreenColor = Color::BLACK;
} state{};

} // namespace Internal

Err init(GraphicsBackend backend);

inline void setClearScreenColor(const Color &color) { Internal::state.clearScreenColor = color; }
inline void clearScreen() { Internal::state.handler->clearScreen(); }

inline GraphicsBackend getBackend() { return Internal::state.backend; }
    
} // namespace Bjr
