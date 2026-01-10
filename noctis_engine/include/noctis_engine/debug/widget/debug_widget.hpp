#pragma once
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API IDebugWidget {
public:
    virtual ~IDebugWidget() = default;
    
    virtual auto draw() -> void = 0;
};

} // namespace NoctisEngine
