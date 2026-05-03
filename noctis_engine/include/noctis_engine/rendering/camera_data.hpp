#pragma once
#include <glm/mat4x4.hpp>

namespace NoctisEngine
{
    
struct alignas(16) CameraData {
    glm::mat4x4 projMat;
    glm::mat4x4 viewMat;
    glm::vec4   pos;
};

} // namespace NoctisEngine
