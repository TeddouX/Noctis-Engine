#pragma once
#include <memory>
#include <string>

#include "../math/color.hpp"
#include "handler.hpp"

namespace NoctisEngine
{
    
class Window;

enum class GraphicsBackend {
    OPENGL,
    // VULKAN
};

class NCENG_API RenderState {
public:
    static auto init(GraphicsBackend backend) -> std::shared_ptr<GraphicsHandler>;
    static auto set_clear_screen_color(Color color) -> void { clearScreenCol_ = color; }

    static auto clear_screen_color() -> Color { return clearScreenCol_; }
    static auto get_backend() -> GraphicsBackend { return backend_; }

    static auto has_context() -> bool { return hasContext_; }
 
private:
    static inline GraphicsBackend backend_;
    static inline Color clearScreenCol_ = Color::BLACK;
    static inline std::shared_ptr<GraphicsHandler> handler_;
    static inline bool hasContext_ = false;

    static auto context_created() -> void { hasContext_ = true; }

    friend NCENG_API Window create_context(int, int, const std::string &);
};

} // namespace NoctisEngine
