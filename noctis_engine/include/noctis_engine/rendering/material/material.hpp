#pragma once
#include <cstdint>
#include "../../math/color.hpp"
#include "../bindless_texture.hpp"

namespace NoctisEngine
{
    
struct alignas(16) MaterialData {
    glm::vec4 baseColor{1};
    // TODO: default to 1x1 white texture
    BindlessTexture albedo{};

    MaterialData() = default;

    MaterialData(BindlessTexture albedo)
        : albedo(albedo)
    {}

    MaterialData(glm::vec4 baseColor)
        : baseColor(baseColor)
    {}
};

using MaterialKey = std::uint32_t;

} // namespace NoctisEngine
