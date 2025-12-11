#pragma once
#include <memory>

#include "../graphics_ctx.hpp"

namespace Bjr
{
    
class OpenGLCtx : public GraphicsCtx {
public:
    static std::shared_ptr<OpenGLCtx> create();

    GraphicsBackend getBackend() const { return GraphicsBackend::OPENGL; }

private:
    OpenGLCtx() = default;
};

} // namespace Bjr
