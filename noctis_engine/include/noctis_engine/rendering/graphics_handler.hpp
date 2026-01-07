#pragma once
#include <stdint.h>

#include "../noctis_engine.hpp"
#include "../math/color.hpp"

namespace NoctisEngine
{
    
class NCENG_API GraphicsHandler {
public:
    GraphicsHandler();
    ~GraphicsHandler() = default;

    void clear_screen() const;
    auto set_backface_culling(bool b) const -> void;
    auto set_depth_testing(bool b) const -> void;
    auto set_clear_screen_color(Color col) -> void;
    auto set_throw_on_err(bool b) -> void;

private:
    Color clearScrCol_;
    bool throwOnErr_ = false;

    static void OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam);
};

} // namespace NoctisEngine
