#pragma once
#include <vector>

#include "../noctis_engine.hpp"
#include "vertex.hpp"

namespace NoctisEngine
{

struct VertexArrayInfo {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
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
