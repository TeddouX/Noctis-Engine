#include <ecs/component/transform.hpp>

#include <core/logging.hpp>

namespace NoctisEngine
{
    
Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 eulerAngles)
    : pos_(position), scale_(scale), rot_(glm::radians(eulerAngles)) {}

Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation)
    : pos_(position), scale_(scale), rot_(rotation) {}

auto Transform::position() -> glm::vec3 & { 
    return pos_; 
}

auto Transform::scale() -> glm::vec3 & { 
    return scale_; 
}

auto Transform::rotation() -> glm::quat & { 
    return rot_; 
}

auto Transform::eulerAngles() const -> glm::vec3 { 
    return glm::eulerAngles(rot_); 
}

auto Transform::model_matrix() const -> glm::mat4 {
    glm::mat4 modelMatrix{1};

    modelMatrix = glm::translate(modelMatrix, pos_);

    glm::mat4 rotationMatrix = glm::toMat4(rot_);
    modelMatrix *= rotationMatrix;
    
    modelMatrix = glm::scale(modelMatrix, scale_);

    return modelMatrix;
}
    
} // namespace NoctisEngine
