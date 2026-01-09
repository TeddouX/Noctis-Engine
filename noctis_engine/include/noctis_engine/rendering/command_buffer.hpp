#pragma once
#include <cstdint>

#include "../ecs/ecs.hpp"
#include "gpu_buffer.hpp"

namespace NoctisEngine
{
    
class NCENG_API CommandBuffer {
public:
    CommandBuffer();

    auto build(const entt::registry &reg) -> std::uint32_t;
    auto bind() -> void; 

private:
    GPUBuffer buf_;
};

} // namespace NoctisEngine
