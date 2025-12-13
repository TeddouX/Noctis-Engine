#pragma once
#include "../vertex_array.hpp"

namespace Bjr
{
    
class VertexArrayOpenGL : public VertexArray {
public:
    VertexArrayOpenGL(const VertexArrayInfo &info);

    void use() override;

private:
    uint32_t VAO_;
    
    bool isIndexed_;
    int indicesSize_;
    int verticesSize_;
};

} // namespace Bjr
