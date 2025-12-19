#pragma once
#include "../vertex_array.hpp"
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{
    
class NCENG_API VertexArrayOpenGL : public VertexArray {
public:
    VertexArrayOpenGL(const VertexArrayInfo &info);

    void use() override;

private:
    uint32_t VAO_;
    
    bool isIndexed_;
    int indicesSize_;
    int verticesSize_;
};

} // namespace NoctisEngine
