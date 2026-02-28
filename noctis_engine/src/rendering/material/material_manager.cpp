#include <rendering/material/material_manager.hpp>
#include <rendering/buffer_utils.hpp>

namespace NoctisEngine
{

MaterialManager::MaterialManager()
    : currKey_(0u)
    , materialOff_(0zu)
{
    materialsSSBO_ = GPUBuffer(sizeof(MaterialData), "material_manager_material_data");
    materialsSSBO_.bind_buffer_base(BufferType::SHADER_STORAGE_BUFFER, 2);
}

auto MaterialManager::upload(const MaterialData &data) -> MaterialKey {
    copy_resize_buffer(
        materialsSSBO_, 
        materialsSSBO_.size() + sizeof(MaterialData), 
        "material_manager_material_data"
    );
    materialsSSBO_.write(get_cpu_buffer_view(data), materialOff_);
    materialsSSBO_.bind_buffer_base(BufferType::SHADER_STORAGE_BUFFER, 2);
    
    materialOff_ += sizeof(MaterialData);
    
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
