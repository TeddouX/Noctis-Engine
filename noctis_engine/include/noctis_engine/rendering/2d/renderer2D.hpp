#pragma once
#include <memory>

#include "../../noctis_engine.hpp"
#include "../mesh/mesh_manager.hpp"
#include "../renderer.hpp"

namespace NoctisEngine
{
    
class NCENG_API Renderer2D : public Renderer {
public:
    Renderer2D(std::shared_ptr<MeshManager> meshManager);

    auto render_entities(entt::registry &reg) -> void override;

private:
};

} // namespace NoctisEngine
