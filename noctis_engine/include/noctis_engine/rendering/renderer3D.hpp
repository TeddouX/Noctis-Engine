#pragma once
#include "renderer.hpp"

namespace NoctisEngine
{
    
class NCENG_API Renderer3D : public Renderer {
public:
    Renderer3D(std::shared_ptr<MeshManager> meshManager);

    auto render_entities(entt::registry &reg) -> void override;
};

} // namespace NoctisEngine
