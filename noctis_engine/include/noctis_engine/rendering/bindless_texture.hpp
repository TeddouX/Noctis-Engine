#pragma once
#include "texture.hpp"

namespace NoctisEngine
{
    
class NCENG_API BindlessTexture {
public:
    BindlessTexture() = default;
    BindlessTexture(Texture tex);

    auto make_resident(bool b) const -> void;
    auto get_handle() const -> std::uint64_t;

private:
    std::uint64_t handle_{};
};

} // namespace NoctisEngine
