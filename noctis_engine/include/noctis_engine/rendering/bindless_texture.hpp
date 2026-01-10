#pragma once
#include "texture.hpp"

namespace NoctisEngine
{

struct DefaultTextures;

class NCENG_API BindlessTexture {
public:
    BindlessTexture() = default;
    BindlessTexture(Texture tex);

    auto make_resident(bool b) const -> void;
    auto get_handle() const -> std::uint64_t;

    static auto default_textures() -> const DefaultTextures &;

private:
    std::uint64_t handle_{};
};

struct DefaultTextures {
    BindlessTexture white_1x1;
};

} // namespace NoctisEngine
