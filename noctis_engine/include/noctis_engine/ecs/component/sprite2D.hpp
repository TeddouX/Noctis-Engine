#pragma once
#include "../../noctis_engine.hpp"
#include "../../rendering/mesh/mesh_view.hpp"

namespace NoctisEngine
{
 
class NCENG_API Sprite2D {
public:
    Sprite2D() = default;
    Sprite2D(int zOrder, MeshView mesh);

    auto get_z_order() const -> int;
    auto get_mesh_view() const -> MeshView;

private:
    int zOrder_;
    MeshView meshView_;
};

} // namespace NoctisEngine
