#pragma once
#include <glm/glm.hpp>

namespace NoctisEngine
{
    
struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec2 texCoords;

    constexpr Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec3 tangent, glm::vec2 texCoords)
        : pos(pos), normal(normal), tangent(tangent), texCoords(texCoords) {}
};

} // namespace NoctisEngine
