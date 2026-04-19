#pragma once
#include <string>

#include "../ecs.hpp"
#include "../../noctis_engine.hpp"

namespace NoctisEngine
{

class NCENG_API ISystemBase {
public:
    virtual ~ISystemBase() = default; 

    virtual auto init() -> void {};
};

template <typename... Components_>
class ISystem : public virtual ISystemBase {
public:
    using base_type = ISystem<Components_...>;

    virtual auto update(float dt, entt::view<entt::get_t<Components_...>> view) -> void {};
};

} // namespace NoctisEngine
