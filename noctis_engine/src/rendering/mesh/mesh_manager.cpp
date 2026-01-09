#include <rendering/mesh/mesh_manager.hpp>

#include <glad/gl.h>

#include <rendering/vertex.hpp>
#include <core/logging.hpp>

namespace NoctisEngine
{
    
MeshManager::MeshManager() 
    : verticesOff_(0zu)
    , indicesOff_(0zu)
{
    verticesBuf_ = GPUBuffer(sizeof(Vertex), "mesh_manager_vertices");
    indicesBuf_  = GPUBuffer(sizeof(std::uint32_t), "mesh_manager_indices");

    constexpr std::string_view name = "mesh_manager_vao";

    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);
    glObjectLabel(GL_VERTEX_ARRAY, VAO_, name.size(), name.data());

    verticesBuf_.bind_as(BufferType::ARRAY_BUFFER);

    generate_vertex_attributes();

    glBindVertexArray(0);
}

auto MeshManager::upload(const MeshInfo &mesh) -> MeshView {
    size_t verticesCount = mesh.vertices.size(); 
    size_t verticesSize = verticesCount * sizeof(Vertex); 
    size_t indicesCount = mesh.indices.size();
    size_t indicesSize = indicesCount * sizeof(std::uint32_t);

    if(copy_resize_buffer(verticesBuf_, verticesOff_ + verticesSize, "mesh_manager_vertices")) {
        glVertexArrayVertexBuffer(VAO_, 0, verticesBuf_.gl_handle(), 0, sizeof(Vertex));

        glBindVertexArray(VAO_);
        generate_vertex_attributes();
        glBindVertexArray(0);
    }

    copy_resize_buffer(indicesBuf_, indicesOff_ + indicesSize, "mesh_manager_indices");

    verticesBuf_.write(get_cpu_buffer_view(mesh.vertices, 0, verticesCount), verticesOff_);
    indicesBuf_.write(get_cpu_buffer_view(mesh.indices, 0, indicesCount), indicesOff_);

    MeshView mv {
        .verticesOffset = verticesOff_ / sizeof(Vertex),
        .verticesCount = verticesCount,
        .indicesOffset = indicesOff_ / sizeof(std::uint32_t),
        .indicesCount = indicesCount,
    };

    verticesOff_ += verticesSize;
    indicesOff_ += indicesSize;

    return mv;
}

auto MeshManager::bind() -> void {
    glBindVertexArray(VAO_);
    indicesBuf_.bind_as(BufferType::ELEMENT_ARRAY_BUFFER);
}

auto MeshManager::generate_vertex_attributes() -> void {
    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos));
    glVertexAttribBinding(0, 0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
    glVertexAttribBinding(1, 0);
    glEnableVertexAttribArray(1);

    glVertexAttribFormat(2, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, tangent));
    glVertexAttribBinding(2, 0);
    glEnableVertexAttribArray(2);

    glVertexAttribFormat(3, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texCoords));
    glVertexAttribBinding(3, 0);
    glEnableVertexAttribArray(3);
}

} // namespace NoctisEngine
