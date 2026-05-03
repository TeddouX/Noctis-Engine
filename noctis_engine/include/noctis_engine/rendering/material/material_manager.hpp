#pragma once
#include "../gpu_buffer.hpp"
#include "../../noctis_engine.hpp"
#include "material.hpp"

namespace NoctisEngine
{
    
class NCENG_API MaterialManager {
public:
    MaterialManager();

    auto upload(const MaterialData &data) -> MaterialKey;
    auto get_material(MaterialKey key) -> MaterialData;
    auto update_material(MaterialKey key, const MaterialData &newData) -> void;

private:
    std::vector<MaterialData>   materialsCPU_;
    GPUBuffer                   materialsSSBO_;
    int                         currKey_;
};

} // namespace NoctisEngine
