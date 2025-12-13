#pragma once
#include <stdint.h>

#include "../ssbo.hpp"

namespace Bjr
{
    
class SSBOOpenGL : public SSBO {
public:
    SSBOOpenGL(int bindPoint);

    void uploadData(size_t size, void *data) override;
    void updateData(size_t offset, size_t size, void *data) override;

private:
    uint32_t ID_;
};
    
} // namespace Bjr
