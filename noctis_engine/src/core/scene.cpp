#include <core/scene.hpp>

#include <ecs/component/transform.hpp>

namespace NoctisEngine
{
    
Scene::Scene(std::shared_ptr<Renderer> renderer)
    : renderer_(renderer)
{
}

auto Scene::create_entity() -> Entity {
    entt::entity e = reg_.create();
    return Entity{e, &reg_};
}

auto Scene::render_all_entities(float dt) -> void {
    renderer_->render(reg_);
}

auto Scene::update(float dt) -> void {
    for (const auto &fun : updateSystems_.get_functions())
        fun(dt, reg_);
}

} // namespace NoctisEngine
