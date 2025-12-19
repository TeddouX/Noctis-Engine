#pragma once
#include <memory>

#include "../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API UniformBuffer {
public:
    static std::unique_ptr<UniformBuffer> Create(int bindPoint);
    
    virtual void rebind(int bind) = 0;
    // virtual void use() = 0;
    virtual void upload_data(size_t size, void *data) = 0;
    virtual void update_data(size_t offset, size_t size, void *data) = 0;
};

} // namespace NoctisEngine

