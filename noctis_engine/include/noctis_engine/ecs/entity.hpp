#pragma once
#include "ecs.hpp"

namespace NoctisEngine
{
    
class Entity {
public:
    Entity() = default;
    Entity(entt::entity entity, entt::registry *reg)
        : entity_(entity)
        , reg_(reg)
    {}

private:
    entt::entity entity_;
    entt::registry *reg_;
};

} // namespace NoctisEngine
