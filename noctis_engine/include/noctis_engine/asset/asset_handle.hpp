#pragma once
#include "../rendering/shader.hpp"
#include "../rendering/texture.hpp"
#include "../core/exception.hpp"

namespace NoctisEngine
{

template <typename AssetType_>
struct AssetHandle {
    int id = -1;

    auto is_valid() -> bool;
    auto expect_valid(const std::string &mess) -> void;
};

using TextureHandle = AssetHandle<Texture>;
using ShaderHandle = AssetHandle<Shader>;

template <typename AssetType_>
auto AssetHandle<AssetType_>::is_valid() -> bool {
    return id > -1;
}

template <typename AssetType_>
auto AssetHandle<AssetType_>::expect_valid(const std::string &mess) -> void {
    if (!is_valid())
        throw Exception("AssetHandle::expect_valid failed: {}", mess);
}

} // namespace NoctisEngine
