#pragma once

namespace NoctisEngine
{
    
struct MouseMouvement {
    double x = 0.0, y = 0.0;
    double xDelta = 0.0, yDelta = 0.0; 
};

enum class MouseButton {
    LEFT,
    RIGHT,
    MIDDLE,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7,
    MAX_MOUSE_BUTTON
};

constexpr size_t NUM_MOUSE_BUTTONS = static_cast<size_t>(MouseButton::MAX_MOUSE_BUTTON) - 1;

} // namespace NoctisEngine

