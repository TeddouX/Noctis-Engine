#pragma once
#include <variant>

namespace NoctisEngine
{

// WE -> Window Event
struct WE_ResizeData { 
    int newWidth;
    int newHeight;
};

struct WindowEvent {
    enum class Type {
        // data will be of type WE_ResizeData
        RESIZE,
        // data will be empty 
        CLOSE
    } type;

    std::variant<
        // Empty struct that gets default initialized by the variant
        std::monostate,
        WE_ResizeData
    > data;
};

} // namespace NoctisEngine
