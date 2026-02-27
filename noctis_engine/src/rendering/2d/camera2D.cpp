#include "rendering/2d/camera2D.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

#include <rendering/camera_data.hpp>
#include <rendering/shader_bindings.hpp>
#include <rendering/buffer_utils.hpp>

namespace NoctisEngine
{
    
Camera2D::Camera2D(float frustumWidth, float frustumHeight, float near, float far)
    : projMat_{glm::ortho(0.f, frustumWidth, frustumHeight, 0.f, near, far)}
    , uniformBuffer_{sizeof(CameraData), "camera2D_ubo"}
{
    uniformBuffer_.bind_buffer_base(BufferType::UNIFORM_BUFFER, ShaderBindings::CAMERA_DATA_UBO);
    pos_ = glm::vec2{-200, 0};
}

auto Camera2D::upload_data() -> void {
    uniformBuffer_.write(get_cpu_buffer_view(
        CameraData{
            .projMat = projMat_,
            .viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(-pos_.x, -pos_.y, 0.0f)),
            .pos = glm::vec4{pos_, 0, 0},
        }
    ), 0);
}

auto Camera2D::set_position(glm::vec2 pos) -> void {
    pos_ = pos;
}

auto Camera2D::translate_by(glm::vec2 translation) -> void {
    pos_ += translation;
}

    
} // namespace NoctisEngine
