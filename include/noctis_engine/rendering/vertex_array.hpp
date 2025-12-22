#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "../noctis_engine.hpp"

namespace NoctisEngine
{
    
struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoords;

    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoords)
        : pos(pos), normal(normal), texCoords(texCoords) {}
};

struct VertexArrayInfo {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

class NCENG_API VertexArray {
public:
    VertexArray(const VertexArrayInfo &info);
    ~VertexArray() = default;

    void use();

private:
    uint32_t VAO_;
    
    bool isIndexed_;
    int indicesSize_;
    int verticesSize_;
};

} // namespace NoctisEngine
