#pragma once
#include "system.hpp"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>


namespace NoctisEngine
{


template<
    template<typename...> class ISystem_Base_, 
    typename System_, 
    typename T = typename System_::base_type
>
struct InheritedArgs;

template<
    template<typename...> class ISystem_Base_, 
    typename System_, 
    typename... Args_
>
struct InheritedArgs<ISystem_Base_, System_, ISystem_Base_<Args_...>> {
    using args_tuple = std::tuple<Args_...>;
};


class NCENG_API SystemStorage {
public:
    using SystemRegistry = std::unordered_map<std::string, std::shared_ptr<ISystemBase>>;
    using UpdateFuncStorage = std::vector<std::function<void(float, entt::registry &)>>;

    SystemStorage() = default;
    ~SystemStorage() = default;

    template <typename System_, typename... Args_>
    requires(std::is_base_of_v<ISystemBase, System_>)
    auto add_system(Args_ &&...args) -> void;

    auto get_update_functions() -> UpdateFuncStorage &;

private:
    SystemRegistry systemRegistry_;
    UpdateFuncStorage updateFunctions_;

    template <typename System_, typename... Components_>
    auto call_update(
        std::shared_ptr<System_> system, 
        float dt, 
        entt::registry &reg, 
        std::tuple<Components_...>) -> void;
};


template <typename System_, typename... Args_>
requires(std::is_base_of_v<ISystemBase, System_>)
auto SystemStorage::add_system(Args_ &&...args) -> void {
    using ComponentsTuple = typename InheritedArgs<ISystem, System_>::args_tuple;

    std::string systemName = typeid(System_).name();

    systemRegistry_.emplace(systemName, std::make_shared<System_>(std::forward<Args_>(args)...));

    auto updateFunc = [&, systemName](float dt, entt::registry &reg) -> void {
        auto system = std::dynamic_pointer_cast<System_>(systemRegistry_.at(systemName));
        call_update(system, dt, reg, ComponentsTuple{});
    };

    updateFunctions_.push_back(updateFunc);
}


template <typename System_, typename... Components_>
auto SystemStorage::call_update(
    std::shared_ptr<System_> system, 
    float dt, 
    entt::registry &reg, 
    std::tuple<Components_...>) -> void {

    system->update(dt, reg.view<Components_...>());
}


} // namespace NoctisEngine
