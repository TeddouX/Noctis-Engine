#pragma once
#include <memory>

#include "../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API SSBO {
public:
    static std::unique_ptr<SSBO> Create(int bindPoint);

    virtual void upload_data(size_t size, void *data) = 0;
    virtual void update_data(size_t offset, size_t size, void *data) = 0;
};

} // namespace NoctisEngine
