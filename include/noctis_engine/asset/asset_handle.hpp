#pragma once
#include "../rendering/shader.hpp"
#include "../rendering/texture.hpp"

namespace NoctisEngine
{

template <typename AssetType_>
struct AssetHandle {
    int id = -1;
};

using TextureHandle = AssetHandle<Texture>;
using ShaderHandle = AssetHandle<Shader>;

} // namespace NoctisEngine
