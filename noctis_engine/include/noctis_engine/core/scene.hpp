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
    Scene(std::shared_ptr<Renderer> renderer);

    auto create_entity() -> Entity;

    template <typename Class_>
        requires(
            std::is_base_of_v<ISystem, Class_> && 
            std::is_default_constructible_v<Class_>
        )
    auto add_system(std::string_view name, auto (Class_::*fun)(float, entt::registry &) -> void) -> void;

    auto update(float dt) -> void;
    auto render_all_entities(float dt) -> void;

    auto get_registry() -> entt::registry & { return reg_; }
    auto get_registry() const -> const entt::registry & { return reg_; }

private:
    SystemStorage renderSystems_;
    SystemStorage updateSystems_;

    entt::registry reg_;

    std::shared_ptr<Renderer> renderer_;
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
