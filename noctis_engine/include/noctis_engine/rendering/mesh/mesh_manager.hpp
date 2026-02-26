#pragma once
#include "../gpu_buffer.hpp"
#include "mesh_info.hpp"
#include "mesh_view.hpp"
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{

class NCENG_API MeshManager {
public:
    MeshManager();

    auto upload(const MeshInfo &mesh) -> MeshView;
    auto bind() -> void;

private:
    std::uint32_t VAO_;

    std::vector<Vertex>        verticesCPUBuf_;
    std::vector<std::uint32_t> indicesCPUBuf_;

    GPUBuffer     verticesGPUBuf_;
    GPUBuffer     indicesGPUBuf_;

    std::size_t   verticesOff_;
    std::size_t   indicesOff_;

    // std::vector<GPUBufferBlock> freeBlocks_;

    auto generate_vertex_attributes() -> void;
};

} // namespace NoctisEngine
