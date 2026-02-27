#pragma once
#include <glm/mat4x4.hpp>

namespace NoctisEngine
{
    
struct CameraData {
    glm::mat4x4 projMat;
    glm::mat4x4 viewMat;
    glm::vec4   pos;
};

} // namespace NoctisEngine
