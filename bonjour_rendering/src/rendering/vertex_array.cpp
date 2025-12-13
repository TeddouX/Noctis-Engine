#include <rendering/vertex_array.hpp>
#include <rendering/opengl/ogl_vertex_array.hpp>
#include <core/bonjour.hpp>

namespace Bjr
{
    
std::unique_ptr<VertexArray> VertexArray::Create(const VertexArrayInfo &info) {
    switch (Bjr::getBackend()) {
        case GraphicsBackend::OPENGL: return std::make_unique<VertexArrayOpenGL>(info);
        default:                      return nullptr;
    }
}
    
} // namespace Bjr
