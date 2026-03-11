#pragma once
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{
    
class DebugUI;

class NCENG_API IDebugWidget {
public:
    virtual ~IDebugWidget() = default;
    
    virtual auto render() -> void = 0;
    virtual auto on_attach(DebugUI *parent) -> void = 0;
};

} // namespace NoctisEngine
