#include <rendering/opengl/ogl_ssbo.hpp>

#include <glad/glad.h>

namespace Bjr
{
    
SSBOOpenGL::SSBOOpenGL(int bindPoint) {
    glGenBuffers(1, &ID_);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindPoint, ID_);
}

void SSBOOpenGL::uploadData(size_t size, void *data) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID_);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBOOpenGL::updateData(size_t offset, size_t size, void *data) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID_);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

} // namespace Bjr
