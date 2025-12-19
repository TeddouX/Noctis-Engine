#pragma once
#include <stdint.h>

#include "../ssbo.hpp"
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API SSBOOpenGL : public SSBO {
public:
    SSBOOpenGL(int bindPoint);

    void upload_data(size_t size, void *data) override;
    void update_data(size_t offset, size_t size, void *data) override;

private:
    uint32_t ID_;
};
    
} // namespace NoctisEngine
