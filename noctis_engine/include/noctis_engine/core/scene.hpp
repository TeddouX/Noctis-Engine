#pragma once
#include "../ecs/ecs.hpp"
#include "../ecs/entity.hpp"

namespace NoctisEngine
{

class Scene {
public:
    Scene() = default;

    auto create_entity() -> Entity;

    template <typename... FuncArgs_>
    auto add_system(std::string_view name, void(*fun)(FuncArgs_...)) -> void;

    auto remove_system(std::string_view name) -> void;

    auto update() -> void;

private:
    std::unordered_map<std::string_view, std::function<void(entt::registry &)>> systems_;
    entt::registry reg_;
};

template <typename... FuncArgs_>
auto Scene::add_system(std::string_view name, void(*fun)(FuncArgs_...)) -> void {
    auto fun = [&](entt::registry &reg) -> void {
        auto view = reg_.view<FuncArgs_...>();
        view.each(fun);
    };

    systems_.emplace(name, fun);
}

} // namespace NoctisEngine
