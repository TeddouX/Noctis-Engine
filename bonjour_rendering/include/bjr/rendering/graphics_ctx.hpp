#pragma once 

namespace Bjr
{
    
enum class GraphicsBackend {
    OPENGL,
    // VULKAN
};

class GraphicsCtx {
public:
    virtual GraphicsBackend getBackend() const = 0;
    // virtual void setClearScreenColor(const glm::vec4 &col) = 0;
    // virtual void clearScreen() = 0;
};

} // namespace Bjr
