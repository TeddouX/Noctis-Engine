#pragma once
#include "../handler.hpp"

#include <stdint.h>

namespace Bjr
{
    
namespace Internal
{
    
class OpenGLHandler : public GraphicsHandler {
public:
    OpenGLHandler() = default;

    void init() override;
    void clearScreen() override;

private:
    static void OpenGLDbgMessCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
        int length, const char* message, const void* userParam);
};

} // namespace Internal

} // namespace Bjr
