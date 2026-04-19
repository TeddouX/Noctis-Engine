#pragma once
#include <filesystem>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "../core/assert.hpp"
#include "../rendering/texture.hpp"
#include "../rendering/shader.hpp"
#include "../rendering/material/material_manager.hpp"
#include "../rendering/mesh/mesh_manager.hpp"
#include "loading.hpp"
#include "asset_handle.hpp"

namespace NoctisEngine
{

constexpr std::string_view PNG_EXTENSION = ".png";
constexpr std::string_view JPEG_EXTENSION = ".jpeg";
constexpr std::string_view GLSL_EXTENSION = ".glsl";

class NCENG_API AssetManager {
public:
    AssetManager();

    // If no name is passed, it will set the asset's name to the file name
    template <typename AssetType_>
    auto load_asset(
        const std::filesystem::path &path, 
        const std::string &name = "") -> AssetHandle<AssetType_>;

    template <typename AssetType_, typename DataType_>
    auto load_from_memory(
        const std::string &name, 
        const DataType_ &data) -> AssetHandle<AssetType_>;

    template <typename AssetType_>
    auto is_valid_handle(AssetHandle<AssetType_> handle) -> bool;

    template <typename AssetType_>
    auto try_get(AssetHandle<AssetType_> handle) -> AssetType_ *;

    // Will throw if the handle is invalid
    template <typename AssetType_>
    auto expect_get(AssetHandle<AssetType_> handle) -> AssetType_ &;

    template <typename AssetType_>
    auto get(AssetHandle<AssetType_> handle) -> std::optional<AssetType_> {
        return try_get(handle);
    }

    auto get_mesh_manager() -> std::shared_ptr<MeshManager>;
    auto get_material_manager() -> std::shared_ptr<MaterialManager>;

private:
    // AssetHandle<Texture>::id is an index into the texture storage
    std::vector<Texture>        textures_;
    std::vector<Shader>         shaders_;
    std::vector<MeshView>       meshViews_;
    std::vector<MaterialKey>    materialKeys_;

    std::shared_ptr<MeshManager>        meshManager_;
    std::shared_ptr<MaterialManager>    materialManager_;

    std::unordered_map<std::string, TextureHandle>  textureCache_;
    std::unordered_map<std::string, ShaderHandle>   shaderCache_;
    std::unordered_map<std::string, MaterialHandle> materialCache_;
    std::unordered_map<std::string, MeshHandle>     meshCache_;

    auto load_texture(const std::filesystem::path &path, const std::string &name) -> TextureHandle;
    auto load_shader(const std::filesystem::path &path, const std::string &name) -> ShaderHandle;
    auto load_mesh_from_memory(const std::string &name, MeshInfo meshInfo) -> MeshHandle;
    auto load_material_from_memory(const std::string &name, MaterialData matData) -> MaterialHandle;

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

template <typename AssetType_, typename DataType_>
auto AssetManager::load_from_memory(
    const std::string &name, 
    const DataType_ &data) -> AssetHandle<AssetType_> {

    if constexpr (std::is_same_v<AssetType_, MeshView>) {
        if constexpr (!std::is_same_v<DataType_, MeshInfo>)
            static_assert(false, "AssetManager::load_from_memory: uncompatible AssetType_ and DataType_");

        return load_mesh_from_memory(name, data);
    } 
    else if constexpr (std::is_same_v<AssetType_, MaterialKey>) {
        if constexpr (!std::is_same_v<DataType_, MaterialData>)
            static_assert(false, "AssetManager::load_from_memory: uncompatible AssetType_ and DataType_");

        return load_material_from_memory(name, data);
    } 
    else
        static_assert(false, "Unsupported AssetType_ passed to AssetManager::load_from_memory");
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
auto AssetManager::expect_get(AssetHandle<AssetType_> handle) -> AssetType_ & {
    auto asset = try_get(handle);

    if (asset == nullptr)
        throw Exception("Failed to get asset. Maybe loading it failed?");

    return *asset;
}

template <typename AssetType_>
auto AssetManager::get_asset_storage() -> std::vector<AssetType_> & {
    if constexpr (std::is_same_v<AssetType_, Texture>)
        return textures_;
    else if constexpr (std::is_same_v<AssetType_, Shader>)
        return shaders_;
    else if constexpr (std::is_same_v<AssetType_, MaterialKey>)
        return materialKeys_;
    else if constexpr (std::is_same_v<AssetType_, MeshView>)
        return meshViews_;
    else
        static_assert(false, "Asset storage of type AssetType_ doesn't exist");
}

} // namespace NoctisEngine
