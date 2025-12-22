#include <rendering/uniform_buffer.hpp>

#include <glad/glad.h>

namespace NoctisEngine
{
    
UniformBuffer::UniformBuffer(int bindPoint)
    : bindPoint_(bindPoint) 
{
    glGenBuffers(1, &ID_);
}

void UniformBuffer::rebind(int bind) {
    glBindBufferRange(GL_UNIFORM_BUFFER, bind, ID_, 0, size_);
}

void UniformBuffer::upload_data(size_t size, void *data) {
    size_ = size;

    glBindBuffer(GL_UNIFORM_BUFFER, ID_);
    glBufferData(GL_UNIFORM_BUFFER, size_, data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, bindPoint_, ID_, 0, size_);
}

void UniformBuffer::update_data(size_t offset, size_t size, void *data) {
    if (size != size_)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, ID_);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size_, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

} // namespace NoctisEngine

