#pragma once
#include <stdint.h>

#include "../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API UniformBuffer {
public:
    UniformBuffer() = default;
    UniformBuffer(int bindPoint);
    ~UniformBuffer() = default;

    void rebind(int bind);
    void upload_data(size_t size, void *data);
    void update_data(size_t offset, size_t size, void *data);

private:
    uint32_t ID_{};
    size_t size_ = 0;
    int bindPoint_;
};

} // namespace NoctisEngine

