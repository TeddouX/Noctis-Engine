#pragma once
#include <string>

#include "../../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API ISystem {
public:
    virtual auto to_string() const -> std::string = 0; 
};

} // namespace NoctisEngine
