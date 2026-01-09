#pragma once 
#include <vector>
#include <unordered_map>
#include <string_view>
#include <memory>
#include <functional>

#include "system.hpp"
#include "../ecs.hpp"

namespace NoctisEngine
{

class SystemStorage {
public:
    using SystemRegistry = std::unordered_map<std::string_view, std::shared_ptr<ISystem>>;
    using FunctionStorage = std::vector<std::function<void(float, entt::registry &)>>;

    SystemStorage() = default;

    template <typename Class_>
        requires(std::is_base_of_v<ISystem, Class_> && std::is_default_constructible_v<Class_>)
    auto add_system(std::string_view name, auto (Class_::*fun)(float, entt::registry &) -> void) -> void;

    auto get_functions() const -> const FunctionStorage & {
        return functions_;
    }

private:
    SystemRegistry systems_;
    FunctionStorage functions_;
};

template <typename Class_>
    requires(std::is_base_of_v<ISystem, Class_> && std::is_default_constructible_v<Class_>)
auto SystemStorage::add_system(std::string_view name, auto (Class_::*fun)(float, entt::registry &) -> void) -> void {
    auto function = [&](float dt, entt::registry &reg) -> void {
        auto system = std::dynamic_pointer_cast<Class_>(systems_.at(name));

        (system.get()->*fun)(dt, reg);
    };
  
    functions_.push_back(function);
}

} // namespace NoctisEngine
