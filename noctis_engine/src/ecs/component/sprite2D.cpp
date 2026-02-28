#include "ecs/component/sprite2D.hpp"

namespace NoctisEngine
{
    
Sprite2D::Sprite2D(int zOrder, MeshView meshView) 
    : zOrder_(zOrder)
    , meshView_(meshView)
{
}

auto Sprite2D::get_z_order() const -> int {
    return zOrder_;
}

auto Sprite2D::get_mesh_view() const -> MeshView {
    return meshView_;
}

} // namespace NoctisEngine
