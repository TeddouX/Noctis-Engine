#pragma once
#include "../../math/math.hpp"
#include "../../noctis_engine.hpp"
#include "transform.hpp"

namespace NoctisEngine
{
    
class NCENG_API Transform2D {
public:
    Transform2D() = default;
    Transform2D(glm::vec2 pos, glm::vec2 scale, glm::quat rot);
    Transform2D(glm::vec2 pos, glm::vec2 scale, glm::vec3 eulerAngles);

    auto position() -> glm::vec2 &;
    auto scale() -> glm::vec2 &;
    auto rotation() -> glm::quat &;
    auto euler_angles() const -> glm::vec3;

    auto model_matrix(int zOrder) const -> glm::mat4;

    auto as_3D() const -> Transform;

private:
    glm::vec2 pos_;
    glm::vec2 scale_;
    glm::quat rot_;
};

} // namespace NoctisEngine
