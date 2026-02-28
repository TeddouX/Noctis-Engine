#pragma once
#include "../ecs/ecs.hpp"
#include "../ecs/entity.hpp"
#include "../rendering/mesh/mesh_manager.hpp"
#include "../rendering/material/material_manager.hpp"
#include "../rendering/gpu_buffer.hpp"
#include "../rendering/renderer.hpp"
#include "../rendering/command_buffer.hpp"
#include "../ecs/system/system.hpp"
#include "../ecs/system/system_storage.hpp"

namespace NoctisEngine
{

class NCENG_API Scene {
public:
    Scene(const std::shared_ptr<MeshManager> &meshManager);

    auto create_entity() -> Entity;

    template <typename Class_>
        requires(
            std::is_base_of_v<ISystem, Class_> && 
            std::is_default_constructible_v<Class_>
        )
    auto add_system(std::string_view name, auto (Class_::*fun)(float, entt::registry &) -> void) -> void;

    auto update(float dt) -> void;
    auto render(float dt) -> void;

private:
    SystemStorage renderSystems_;
    SystemStorage updateSystems_;

    entt::registry reg_;

    Renderer renderer_;
};

template <typename Class_>
    requires(
        std::is_base_of_v<ISystem, Class_> && 
        std::is_default_constructible_v<Class_>
    )
auto Scene::add_system(std::string_view name, auto (Class_::*fun)(float, entt::registry &) -> void) -> void {
    updateSystems_.add_system(name, fun);
}

} // namespace NoctisEngine
