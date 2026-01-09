#pragma once
#include "ecs.hpp"
#include "../core/logging.hpp"
#include "../core/exception.hpp"

namespace NoctisEngine
{
    
class Entity {
public:
    Entity() = default;
    Entity(entt::entity entity, entt::registry *reg)
        : entity_(entity)
        , reg_(reg)
    {}

    template <typename T>
    void add_component(T &&comp) {
        using ComponentType = std::decay_t<T>;
        if (reg_->all_of<ComponentType>(entity_)) {
            Log::Warn("Tried to add the same component two times to one entity. If this is intended behaviour, use Entity::add_component_or_replace.");
            return;
        }

        reg_->emplace<ComponentType>(entity_, std::move(comp));
    }

    template <typename T>
    void add_component_or_replace(T &&comp) {
        using ComponentType = std::decay_t<T>;
        reg_->emplace_or_replace<ComponentType>(entity_, std::move(comp));
    }

    template <typename T>
    T &get_component() {
        T *ptr = reg_->try_get<T>(entity_);
        
        if (!ptr)
            throw Exception("Tried getting a component from an entity that doesn't own it.");

        return *ptr;
    }

    template <typename T>
    const T &get_component() const {
        const T *ptr = reg_->try_get<T>(entity_);
        
        if (!ptr)
            throw Exception("Tried getting a component from an entity that doesn't own it.");

        return *ptr;
    }

    template <typename T>
    void remove_component() {
        reg_->remove<T>(entity_);
    }

private:
    entt::entity entity_;
    entt::registry *reg_;
};

} // namespace NoctisEngine
