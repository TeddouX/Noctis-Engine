#pragma once
#include <glm/mat4x4.hpp>

#include "../gpu_buffer.hpp"

namespace NoctisEngine
{
 
class NCENG_API Camera2D {
public:
    Camera2D(float frustumWidth, float frustumHeight, float near, float far);
    ~Camera2D() = default;

    auto upload_data() -> void;

    auto set_position(glm::vec2 pos) -> void;
    auto translate_by(glm::vec2 translation) -> void;

private:
    GPUBuffer uniformBuffer_;

    glm::mat4 projMat_;
    glm::vec2 pos_;
};

} // namespace NoctisEngine
