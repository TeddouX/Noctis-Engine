#pragma once
#include "../gpu_buffer.hpp"
#include "material.hpp"

namespace NoctisEngine
{
    
class MaterialManager {
public:
    MaterialManager();

    auto upload(const MaterialData &data) -> MaterialKey;
    auto get_material(MaterialKey key) -> MaterialData;

private:
    GPUBuffer     materialsSSBO_;
    std::size_t   materialOff_;
    std::uint32_t currKey_;
};

} // namespace NoctisEngine
