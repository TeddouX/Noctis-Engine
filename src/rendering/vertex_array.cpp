#include <rendering/vertex_array.hpp>

#include <glad/glad.h>

namespace NoctisEngine
{
    
template <typename T>
static void create_buffer(GLenum target, GLenum usage, const std::vector<T> &data, uint32_t &id) {
    glGenBuffers(1, &id);
    glBindBuffer(target, id);
    glBufferData(target, data.size() * sizeof(T), data.data(), usage);
}

VertexArray::VertexArray(const VertexArrayInfo &info) {
    // VAO should always be created first for it to 
    // observe all other buffer being created
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    verticesSize_ = static_cast<int>(info.vertices.size());
    
    uint32_t VBO;
    create_buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, info.vertices, VBO);

    if (!info.indices.empty()) {
        indicesSize_ = static_cast<int>(info.indices.size());
        isIndexed_ = true;

        uint32_t EBO;
        create_buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, info.indices, EBO);
    } 
    else
        isIndexed_ = false;

    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
}

void VertexArray::use() {
    glBindVertexArray(VAO_);

    if (isIndexed_)
        glDrawElements(GL_TRIANGLES, indicesSize_, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, verticesSize_);
}

} // namespace NoctisEngine
