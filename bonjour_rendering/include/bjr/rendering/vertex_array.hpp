#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <memory>

namespace Bjr
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

class VertexArray {
public:
    static std::unique_ptr<VertexArray> Create(const VertexArrayInfo &info);

    virtual void use() = 0; 
};

} // namespace Bjr
