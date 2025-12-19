#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

#include "../noctis_engine.hpp"

namespace NoctisEngine
{
    
class UniformBuffer;
class GraphicsCtx;

class NCENG_API Camera {
public:
    Camera() = default;
    Camera(glm::vec3 pos, 
        float aspectRatio, 
        float fov, 
        float near, float far);

    void rotate_by(float yaw, float pitch);
    void upload_data();

private:
    std::shared_ptr<UniformBuffer> uniformBuffer_;
    glm::vec3 pos_;
    float fov_;
    float aspectRatio_;
    float near_, far_;
    float yaw_ = 0.f, pitch_ = 0.f;

    struct Data {
        glm::mat4x4 projMat;
        glm::mat4x4 viewMat;
        glm::vec4   pos;
    } data_;
};

} // namespace NoctisEngine
