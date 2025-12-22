#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

#include "../noctis_engine.hpp"
#include "uniform_buffer.hpp"

namespace NoctisEngine
{
    
class NCENG_API Camera {
public:
    Camera() = default;
    Camera(glm::vec3 pos, 
        float aspectRatio, 
        float fov, 
        float near, float far);

    void rotate_by_clamped(float yaw, float pitch);
    void upload_data();

    auto get_position() -> glm::vec3 { return pos_; }
    auto set_position(glm::vec3 pos) -> void;
    auto translate_by(glm::vec3 translation) -> void;

    auto up() -> glm::vec3 { return up_; }
    auto right() -> glm::vec3 { return right_; }
    auto forward() -> glm::vec3 { return forward_; }

private:
    UniformBuffer uniformBuffer_;
    glm::vec3 pos_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 forward_;
    float fov_;
    float aspectRatio_;
    float near_, far_;
    // In degrees
    float yaw_, pitch_;

    struct Data {
        glm::mat4x4 projMat;
        glm::mat4x4 viewMat;
        glm::vec4   pos;
    } data_;

    auto update_view_mat() -> void;
};

} // namespace NoctisEngine
