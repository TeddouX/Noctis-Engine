#include <rendering/camera.hpp>
#include <rendering/uniform_buffer.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace NoctisEngine
{
    
Camera::Camera(glm::vec3 pos, 
    float aspectRatio, 
    float fov, 
    float near, float far) 
    : pos_(pos), aspectRatio_(aspectRatio), fov_(fov), near_(near), far_(far)
{
    uniformBuffer_ = UniformBuffer::Create(0);
    uniformBuffer_->upload_data(sizeof(Camera::Data), &data_);
}

void Camera::rotate_by(float yaw, float pitch) {
    yaw_ += yaw;
	pitch_ += pitch;

	if (pitch_ > 89.0f)
		pitch_ = 89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;
}

void Camera::upload_data() {
    data_.projMat = glm::perspective(glm::radians(fov_), aspectRatio_, near_, far_);

    glm::vec3 front(
        cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)),
	    sin(glm::radians(pitch_)),
	    sin(glm::radians(yaw_)) * cos(glm::radians(pitch_))
    );

    data_.viewMat = glm::lookAt(pos_, glm::normalize(front), glm::vec3(0, 1, 0));
    data_.pos = glm::vec4(pos_, 0);

    uniformBuffer_->update_data(0, sizeof(Camera::Data), &data_);
}

} // namespace NoctisEngine
