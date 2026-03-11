#pragma once
#include "mesh/mesh_manager.hpp"
#include "material/material_manager.hpp"
#include "../ecs/ecs.hpp"

namespace NoctisEngine
{
    
class Renderer {
public:
    Renderer(std::shared_ptr<MeshManager> meshManager);

    auto render(entt::registry &reg) -> void;

private:
    std::shared_ptr<MeshManager> meshManager_;
    GPUBuffer                    objectsSSBO_;
    GPUBuffer                    commandBuf_;
};

} // namespace NoctisEngine
