#pragma once
#include <memory>

namespace Bjr
{
    
class SSBO {
public:
    static std::unique_ptr<SSBO> Create(int bindPoint);

    virtual void uploadData(size_t size, void *data) = 0;
    virtual void updateData(size_t offset, size_t size, void *data) = 0;
};

} // namespace Bjr
