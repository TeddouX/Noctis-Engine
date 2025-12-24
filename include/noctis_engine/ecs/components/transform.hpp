#pragma once
#include "../../math/math.hpp"

namespace NoctisEngine
{
    
class Transform {
public:
    Transform() = default;

    Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 eulerAngles)
        : pos_(position), scale_(scale), rot_(glm::radians(eulerAngles)) {}

    Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation)
        : pos_(position), scale_(scale), rot_(rotation) {}

    auto position() const -> const glm::vec3 & { return pos_; }
    auto scale() const -> const glm::vec3 & { return scale_; }
    auto rotation() const -> const glm::quat & { return rot_; }
    auto eulerAngles() const -> const glm::vec3 & { return glm::eulerAngles(rot_); }

private:
    glm::vec3 pos_;
    glm::vec3 scale_;
    glm::quat rot_;
};

} // namespace NoctisEngine

