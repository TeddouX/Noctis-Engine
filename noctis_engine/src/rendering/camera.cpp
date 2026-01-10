#include <rendering/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <core/logging.hpp>
#include <rendering/buffer_utils.hpp>

namespace NoctisEngine
{

constexpr glm::vec3 WORLD_UP{0, 1, 0};

static auto create_forward_vec(float yawRad, float pitchRad) -> glm::vec3 {
    return glm::normalize(glm::vec3{
        glm::cos(yawRad) * glm::cos(pitchRad), 
        glm::sin(pitchRad), 
        glm::sin(yawRad) * glm::cos(pitchRad)
    });
}

Camera::Camera(glm::vec3 pos, 
    float aspectRatio, 
    float fov, 
    float near, float far) 
    : pos_(pos)
    , aspectRatio_(aspectRatio)
    , fov_(fov)
    , near_(near)
    , far_(far)
    , yaw_(0.0f)
    , pitch_(0.0f)
    , up_(WORLD_UP)
    , forward_(glm::vec3{0})
    , right_(glm::normalize(glm::cross(forward_, up_)))
    , uniformBuffer_(sizeof(Camera::Data), "camera_UBO")
    , data_{ .projMat = glm::perspective(glm::radians(fov_), aspectRatio_, near_, far_) }
    , dirty_(true)
{
    uniformBuffer_.bind_buffer_base(BufferType::UNIFORM_BUFFER, 0);
}

void Camera::rotate_by_clamped(float yaw, float pitch) {
    yaw_ += yaw;
    pitch_ += pitch;

    if (pitch_ > 89.0f)
        pitch_ = 89.0f;
    else if (pitch_ < -89.0f)
        pitch_ = -89.0f;

    forward_ = create_forward_vec(glm::radians(yaw_), glm::radians(pitch_));
    right_ = glm::normalize(glm::cross(forward_, WORLD_UP));
    up_ = glm::normalize(glm::cross(right_, forward_));

    update_view_mat();
}

auto Camera::set_position(glm::vec3 pos) -> void { 
    pos_ = pos;
    data_.pos = glm::vec4(pos_, 0);

    update_view_mat(); 
}

auto Camera::translate_by(glm::vec3 translation) -> void { 
    pos_ += translation;
    data_.pos = glm::vec4(pos_, 0);

    update_view_mat(); 
}

void Camera::upload_data() {
    if (dirty_) {
        uniformBuffer_.write(get_cpu_buffer_view(data_), 0);
        dirty_ = false;
    }
}

auto Camera::update_view_mat() -> void {
    data_.viewMat = glm::lookAt(pos_, pos_ + glm::normalize(forward_), up_);

    dirty_ = true;
}

} // namespace NoctisEngine
