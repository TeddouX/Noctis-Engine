#include <rendering/vertex_array.hpp>

#include <glad/glad.h>

#include <noctis_engine/rendering/gpu_buffer.hpp>

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
    
    GPUBuffer vertexBuffer(info.vertices.size() * sizeof(Vertex), info.name);
    vertexBuffer.bind_as(BufferType::ARRAY_BUFFER);
    vertexBuffer.write(
        get_cpu_buffer_view(info.vertices, 0, info.vertices.size()), 0, 
        WriteType::DYNAMIC_DRAW
    );

    if (!info.indices.empty()) {
        indicesSize_ = static_cast<int>(info.indices.size());
        isIndexed_ = true;

        GPUBuffer vertexBuffer(info.indices.size() * sizeof(uint32_t), info.name);
        vertexBuffer.bind_as(BufferType::ELEMENT_ARRAY_BUFFER);
        vertexBuffer.write(
            get_cpu_buffer_view(info.indices, 0, info.indices.size()), 0, 
            WriteType::DYNAMIC_DRAW
        );
    } 
    else
        isIndexed_ = false;

    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

void VertexArray::use() {
    glBindVertexArray(VAO_);

    if (isIndexed_)
        glDrawElements(GL_TRIANGLES, indicesSize_, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, verticesSize_);

    glBindVertexArray(0);
}

} // namespace NoctisEngine
