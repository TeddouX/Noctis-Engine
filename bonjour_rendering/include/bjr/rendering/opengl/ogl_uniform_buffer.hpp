#pragma once
#include "../uniform_buffer.hpp"

namespace Bjr
{
    
class UniformBufferOpenGL : public UniformBuffer {
public:
    UniformBufferOpenGL(int bindPoint);

    void rebind(int bind) override;
    // void use() override;
    void uploadData(size_t size, void *data) override;
    void updateData(size_t offset, size_t size, void *data) override;

private:
    uint32_t ID_;
    size_t size_ = 0;
    int bindPoint_;
};

} // namespace Bjr

