#pragma once
#include <filesystem>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "../core/assert.hpp"
#include "../rendering/texture.hpp"
#include "../rendering/shader.hpp"
#include "loading.hpp"
#include "asset_handle.hpp"

namespace NoctisEngine
{

constexpr std::string_view PNG_EXTENSION = ".png";
constexpr std::string_view JPEG_EXTENSION = ".jpeg";
constexpr std::string_view GLSL_EXTENSION = ".glsl";

class NCENG_API AssetManager {
public:
    AssetManager() = default;

    // If no name is passed, it will set the asset's name to the file name
    template <typename AssetType_>
    auto load_asset(
        const std::filesystem::path &path, 
        const std::string &name = "") -> AssetHandle<AssetType_>;

    template <typename AssetType_>
    auto is_valid_handle(AssetHandle<AssetType_> handle) -> bool;

    template <typename AssetType_>
    auto try_get(AssetHandle<AssetType_> handle) -> AssetType_ *;

    template <typename AssetType_>
    auto get(AssetHandle<AssetType_> handle) -> std::optional<AssetType_> {
        return try_get(handle);
    }

private:
    std::vector<Texture> textures_;
    std::vector<Shader>  shaders_;

    // AssetHandle::id is an index into the texture storage
    std::unordered_map<std::filesystem::path, TextureHandle> textureCache_;
    std::unordered_map<std::filesystem::path, ShaderHandle>  shaderCache_;

    auto load_texture(const std::filesystem::path &path, const std::string &name) -> TextureHandle;
    auto load_shader(const std::filesystem::path &path, const std::string &name) -> ShaderHandle;

    template <typename AssetType_>
    auto get_asset_storage() -> std::vector<AssetType_> &;
};

template <typename AssetType_>
auto AssetManager::load_asset(
    const std::filesystem::path &path, 
    const std::string &name) -> AssetHandle<AssetType_> {

    if (!std::filesystem::exists(path)) {
        Log::Error("{} does not exist", path.string());
        return AssetHandle<AssetType_>{};
    }

    const std::string extension = path.extension().string();
    const std::string filename = path.filename().string();
    const std::string realName = name.empty() ? path.stem().string() : name;

    if constexpr (std::is_same_v<AssetType_, Texture>) {
        if (extension != PNG_EXTENSION && extension != JPEG_EXTENSION) {
            Log::Error("{} is not an image", path.string());
            return AssetHandle<AssetType_>{};
        }

        return load_texture(path, realName);
    }
    else if constexpr (std::is_same_v<AssetType_, Shader>) {
        if (extension != GLSL_EXTENSION) {
            Log::Error("{} is not a shader", path.string());
            return AssetHandle<AssetType_>{};
        }

        return load_shader(path, realName);
    }
    else {
        static_assert(false, "Unsupported AssetType_ passed to AssetManager::load_asset");
        std::unreachable();
    }
}

template <typename AssetType_>
auto AssetManager::is_valid_handle(AssetHandle<AssetType_> handle) -> bool {
    int idx = handle.id;
    if (idx < 0)
        return false;

    std::vector<AssetType_> &assetStorage = get_asset_storage<AssetType_>();
    return idx < assetStorage.size();
}

template <typename AssetType_>
auto AssetManager::try_get(AssetHandle<AssetType_> handle) -> AssetType_ * {
    if (!is_valid_handle(handle))
        return nullptr;
    
    std::vector<AssetType_> &assetStorage = get_asset_storage<AssetType_>();
    return &assetStorage.at(handle.id);
}

template <typename AssetType_>
auto AssetManager::get_asset_storage() -> std::vector<AssetType_> & {
    if constexpr (std::is_same_v<AssetType_, Texture>)
        return textures_;
    else if constexpr (std::is_same_v<AssetType_, Shader>)
        return shaders_;
    else {
        static_assert(false, "Asset storage of type AssetType_ doesn't exist");
        std::unreachable();
    }   
}

} // namespace NoctisEngine
