#pragma once
#include <glm/glm.hpp>

namespace NoctisEngine
{
    
struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoords;

    constexpr Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoords)
        : pos(pos), normal(normal), texCoords(texCoords) {}
};

} // namespace NoctisEngine
