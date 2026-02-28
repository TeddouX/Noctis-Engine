#pragma once
#include "mesh_info.hpp"
#include "../vertex.hpp"

namespace NoctisEngine::DefaultMeshes
{

static const NoctisEngine::MeshInfo QUAD {
    "default_quad",
    {
        NoctisEngine::Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec3(0), glm::vec2(1, 1)),
        NoctisEngine::Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0), glm::vec3(0), glm::vec2(0, 1)),
        NoctisEngine::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0), glm::vec2(0, 0)),
        NoctisEngine::Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0), glm::vec2(1, 0)),
    },
    {0, 1, 2, 2, 3, 0}
};

} // namespace NoctisEngine
