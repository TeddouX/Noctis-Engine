#pragma once
#include <stdint.h>

#include "../handler.hpp"
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API OpenGLHandler : public GraphicsHandler {
public:
    OpenGLHandler();

    void clear_screen() override;

private:
    static void OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam);
};

} // namespace NoctisEngine
