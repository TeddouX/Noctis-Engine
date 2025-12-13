#pragma once

namespace Bjr
{
  
namespace Internal
{
    
class GraphicsHandler {
public:
    virtual void init() = 0;
    virtual void clearScreen() = 0;
};

} // namespace Internal

} // namespace Bjr
