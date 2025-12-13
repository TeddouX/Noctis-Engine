#pragma once
#include <memory>

namespace Bjr
{
    
class UniformBuffer {
public:
    static std::unique_ptr<UniformBuffer> Create(int bindPoint);
    
    virtual void rebind(int bind) = 0;
    // virtual void use() = 0;
    virtual void uploadData(size_t size, void *data) = 0;
    virtual void updateData(size_t offset, size_t size, void *data) = 0;
};

} // namespace Bjr

