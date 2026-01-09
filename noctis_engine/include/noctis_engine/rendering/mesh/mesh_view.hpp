#pragma once
#include <cstddef>

namespace NoctisEngine
{
    
struct MeshView {
    std::size_t verticesOffset;
    std::size_t verticesCount;
    std::size_t indicesOffset;
    std::size_t indicesCount;
};

} // namespace NoctisEngine
