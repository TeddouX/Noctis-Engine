#include <rendering/material/material_manager.hpp>
#include <rendering/buffer_utils.hpp>

namespace NoctisEngine
{

MaterialManager::MaterialManager()
    : currKey_(0u)
{
    materialsSSBO_ = GPUBuffer(1, "material_manager_material_data");
    materialsSSBO_.bind_buffer_base(BufferType::SHADER_STORAGE_BUFFER, 2);
}

auto MaterialManager::upload(const MaterialData &data) -> MaterialKey {
    materialsCPU_.push_back(data);

    if (resize_buffer(materialsSSBO_, materialsCPU_)) {
        materialsSSBO_.write(get_cpu_buffer_view(materialsCPU_, 0, materialsCPU_.size()), 0);
        materialsSSBO_.bind_buffer_base(BufferType::SHADER_STORAGE_BUFFER, 2);
    }
    
    return currKey_++;
}

auto MaterialManager::get_material(MaterialKey key) -> MaterialData {
    size_t idxBytes = key * sizeof(MaterialData);
    if (idxBytes > materialsSSBO_.size())
        throw Exception("Key {} is invalid", key);

    MaterialData data{};
    materialsSSBO_.get_data(idxBytes, get_cpu_buffer_view(data));
    return data;
}

} // namespace NoctisEngine
