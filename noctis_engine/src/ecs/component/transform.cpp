#include <ecs/component/transform.hpp>

#include <core/logging.hpp>

namespace NoctisEngine
{
    
Transform::Transform(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &eulerAngles) 
    : cachedModelMatrix_{1}
    , dirty_{false}
{
    set_position(position);
    set_scale(scale);
    set_euler_angles(eulerAngles);
}

Transform::Transform(const glm::vec3 &position, const glm::vec3 &scale, const glm::quat &rotation) 
    : cachedModelMatrix_{1}
    , dirty_{false}
{
    set_position(position);
    set_scale(scale);
    set_rotation(rotation);
}

Transform::Transform(const glm::vec2 &position, const glm::vec2 &scale, const glm::vec3 &eulerAngles) 
    : cachedModelMatrix_{1}
    , dirty_{false}
{
    set_position(position);
    set_scale(scale);
    set_euler_angles(eulerAngles);
}

Transform::Transform(const glm::vec2 &position, const glm::vec2 &scale, const glm::quat &rotation) 
    : cachedModelMatrix_{1}
    , dirty_{false}
{
    set_position(position);
    set_scale(scale);
    set_rotation(rotation);
}

auto Transform::set_position(const glm::vec3 &pos) -> void {
    pos_ = pos;
    dirty_ = true;
}

auto Transform::set_scale(const glm::vec3 &scale) -> void {
    scale_ = scale;
    dirty_ = true;
}

auto Transform::set_position(const glm::vec2 &pos) -> void {
    set_position(glm::vec3(pos, 0));
}

auto Transform::set_scale(const glm::vec2 &scale) -> void {
    set_scale(glm::vec3(scale, 1));
}

auto Transform::set_rotation(const glm::quat &rot) -> void {
    rotation_ = rot;
    dirty_ = true;
}

auto Transform::set_euler_angles(const glm::vec3 &rot) -> void {
    set_rotation(glm::quat{rot});
}

auto Transform::get_position() const -> const glm::vec3 & {
    return pos_;
}

auto Transform::get_scale() const -> const glm::vec3 & {
    return scale_;
}

auto Transform::get_rotation() const -> const glm::quat & {
    return rotation_;
}

auto Transform::get_euler_angles() const -> glm::vec3 {
    return glm::eulerAngles(rotation_);
}

auto Transform::model_matrix() const -> const glm::mat4 & {
    if (dirty_) {
        cachedModelMatrix_ = glm::translate(glm::mat4{1}, pos_)
            * glm::toMat4(rotation_)
            * glm::scale(glm::mat4{1}, scale_);
        dirty_ = false;
    }

    return cachedModelMatrix_;
}
    
} // namespace NoctisEngine
