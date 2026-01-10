#pragma once
#include <cstdint>
#include "../../math/color.hpp"
#include "../bindless_texture.hpp"

namespace NoctisEngine
{
    
struct alignas(16) MaterialData {
    glm::vec4 baseColor{1};
    BindlessTexture albedo{BindlessTexture::default_textures().white_1x1};

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
