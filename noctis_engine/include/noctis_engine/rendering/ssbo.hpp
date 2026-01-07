#pragma once
#include <stdint.h>

#include "../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API SSBO {
public:
    SSBO() = default;
    SSBO(int bindPoint);
    ~SSBO() = default;

    void upload_data(size_t size, void *data);
    void update_data(size_t offset, size_t size, void *data);

private:
    uint32_t ID_;
};
    
} // namespace NoctisEngine
