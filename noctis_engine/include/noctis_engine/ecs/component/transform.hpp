#pragma once
#include "../../math/math.hpp"
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API Transform {
public:
    Transform() = default;
    Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 eulerAngles);
    Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation);

    auto position() -> glm::vec3 &;
    auto scale() -> glm::vec3 &;
    auto rotation() -> glm::quat &;
    auto eulerAngles() const -> glm::vec3;

    auto model_matrix() const -> glm::mat4;

private:
    glm::vec3 pos_;
    glm::vec3 scale_;
    glm::quat rot_;
};

} // namespace NoctisEngine

