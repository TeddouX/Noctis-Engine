#pragma once
#include "gpu_buffer.hpp"

namespace NoctisEngine
{
    
class MaterialManager {
public:
    MaterialManager() = default;

private:
    GPUBuffer materialsSSBO_;
};

} // namespace NoctisEngine
