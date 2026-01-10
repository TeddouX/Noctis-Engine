#pragma once
#include <vector>
#include <string_view>

#include "../../noctis_engine.hpp"
#include "../vertex.hpp"

namespace NoctisEngine
{

struct MeshInfo {
    std::string_view name;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    constexpr MeshInfo(std::string_view name, const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices)
        : name(name) 
        , vertices(vertices)
        , indices(indices)
    {}
};

} // namespace NoctisEngine
