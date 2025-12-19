#pragma once
#include "../uniform_buffer.hpp"
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API UniformBufferOpenGL : public UniformBuffer {
public:
    UniformBufferOpenGL(int bindPoint);

    void rebind(int bind) override;
    // void use() override;
    void upload_data(size_t size, void *data) override;
    void update_data(size_t offset, size_t size, void *data) override;

private:
    uint32_t ID_;
    size_t size_ = 0;
    int bindPoint_;
};

} // namespace NoctisEngine

