#include "ecs/component/transform2D.hpp"

namespace NoctisEngine
{
    
Transform2D::Transform2D(glm::vec2 pos, glm::vec2 scale, glm::quat rot) 
    : pos_(pos)
    , scale_(scale)
    , rot_(rot)
{
}

Transform2D::Transform2D(glm::vec2 pos, glm::vec2 scale, glm::vec3 eulerAngles) 
    : pos_(pos)
    , scale_(scale)
    , rot_(glm::radians(eulerAngles))
{
}

auto Transform2D::position() -> glm::vec2 & {
    return pos_;
}

auto Transform2D::scale() -> glm::vec2 & {
    return scale_;
}

auto Transform2D::rotation() -> glm::quat & {
    return rot_;
}

auto Transform2D::euler_angles() const -> glm::vec3 {
    return glm::eulerAngles(rot_);
}

auto Transform2D::model_matrix(int zOrder) const -> glm::mat4 {
    glm::mat4 modelMatrix{1};

    modelMatrix = glm::translate(modelMatrix, glm::vec3(pos_, zOrder));

    glm::mat4 rotationMatrix = glm::toMat4(rot_);
    modelMatrix *= rotationMatrix;
    
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale_, 0));

    return modelMatrix;
}

auto Transform2D::as_3D() const -> Transform {
    return Transform{glm::vec3(pos_, 0), glm::vec3(scale_, 0), rot_};
}

} // namespace NoctisEngine
