#pragma once
#include <cstdint>
#include "../../math/color.hpp"
#include "../bindless_texture.hpp"

namespace NoctisEngine
{
    
struct MaterialData {
    glm::vec3 baseColor{1};
    float alpha = 1.f;

    BindlessTexture albedo{BindlessTexture::default_textures().white_1x1};
};

using MaterialKey = std::uint32_t;

} // namespace NoctisEngine
