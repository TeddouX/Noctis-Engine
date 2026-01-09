#pragma once
#include <cstdint>
#include "../../math/color.hpp"
#include "../rendering/bindless_texture.hpp"

namespace NoctisEngine
{
    
struct MaterialData {
    glm::vec4 baseColor{1};
    BindlessTexture albedo;

    MaterialData(BindlessTexture albedo)
        : albedo(albedo)
    {}

    MaterialData(glm::vec4 baseColor)
        : baseColor(baseColor)
    {}
};

using MaterialKey = std::uint32_t;

} // namespace NoctisEngine
