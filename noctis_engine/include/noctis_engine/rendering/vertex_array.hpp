#pragma once
#include <vector>
#include <string_view>

#include "../noctis_engine.hpp"
#include "vertex.hpp"

namespace NoctisEngine
{

struct VertexArrayInfo {
    std::string_view name;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    constexpr VertexArrayInfo(std::string_view name, const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices)
        : name(name) 
        , vertices(vertices)
        , indices(indices)
    {}
};

class NCENG_API VertexArray {
public:
    VertexArray() = default;
    VertexArray(const VertexArrayInfo &info);
    
    ~VertexArray() = default;

    void use();

private:
    uint32_t VAO_{};
    
    bool isIndexed_;
    int indicesSize_;
    int verticesSize_;
};

} // namespace NoctisEngine
