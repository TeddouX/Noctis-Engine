#include <core/scene.hpp>

namespace NoctisEngine
{
    
auto Scene::create_entity() -> Entity {
    entt::entity e = reg_.create();
    return Entity{e, &reg_};
}

auto Scene::remove_system(std::string_view name) -> void {
    systems_.erase(name);
}

auto Scene::update() -> void {
    for (auto &[name, fun] : systems_)
        fun(reg_);
}

} // namespace NoctisEngine
