#pragma once
#include <stdint.h>

#include "../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API GraphicsHandler {
public:
    GraphicsHandler();
    ~GraphicsHandler() = default;

    void clear_screen();

private:
    static void OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam);
};

} // namespace NoctisEngine
