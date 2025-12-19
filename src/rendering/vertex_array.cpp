#include <rendering/vertex_array.hpp>

#include <rendering/opengl/ogl_vertex_array.hpp>
#include <rendering/render_state.hpp>

namespace NoctisEngine
{
    
std::unique_ptr<VertexArray> VertexArray::Create(const VertexArrayInfo &info) {
    switch (RenderState::get_backend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<VertexArrayOpenGL>(info);
        default:                      return nullptr;
    }
}
    
} // namespace NoctisEngine
