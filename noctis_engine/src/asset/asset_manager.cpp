#include <asset/asset_manager.hpp>

#include <fstream>
#include <functional>

namespace NoctisEngine
{

template <typename AssetType_>
static auto create_handle(
    std::vector<AssetType_> &assetStorage, 
    const AssetType_ &asset) -> AssetHandle<AssetType_> {
    
    assetStorage.push_back(asset);
    
    int pos = assetStorage.size() - 1;
    AssetHandle<AssetType_> handle{
        .id = pos
    };

    return handle;
}

template <typename AssetType_>
static auto load_with_cache(
    std::unordered_map<std::string, AssetHandle<AssetType_>> &cache,
    std::vector<AssetType_> &storage,
    const std::string &name,
    std::function<std::optional<AssetType_> (void)> loader,
    std::string_view assetKind) -> AssetHandle<AssetType_> {

    if (auto it = cache.find(name); it != cache.end()) {
        Log::Debug("Loaded {} '{}' from cache. Check for duplicate uploads.", assetKind, name);
        return it->second;
    }

    std::optional<AssetType_> asset = loader();
    if (!asset) {
        Log::Error("Failed to load {} '{}'", assetKind, name);
        return AssetHandle<AssetType_>{};
    }

    Log::Debug("Successfully loaded {} '{}'", assetKind, name);

    auto handle = create_handle(storage, asset.value());
    cache.emplace(name, handle);

    return handle;
}


AssetManager::AssetManager() 
    : meshManager_(std::make_shared<MeshManager>())
    , materialManager_(std::make_shared<MaterialManager>())
{}


auto AssetManager::get_mesh_manager() -> std::shared_ptr<MeshManager> {
    return meshManager_;
}


auto AssetManager::get_material_manager() -> std::shared_ptr<MaterialManager> {
    return materialManager_;
}


auto AssetManager::load_texture(
    const std::filesystem::path &path, 
    const std::string &name) -> TextureHandle {

    return load_with_cache<Texture>(
        textureCache_,
        textures_,
        name, 
        [&] -> std::optional<Texture> { 
            return Internal::load_texture(path, name); 
        }, 
        "texture"
    );
}


auto AssetManager::load_shader(
    const std::filesystem::path &path, 
    const std::string &name) -> ShaderHandle {

    return load_with_cache<Shader>(
        shaderCache_,
        shaders_,
        name, 
        [&] -> std::optional<Shader> { 
            std::ifstream ifs;

            std::stringstream buf;
            ifs.open(path);
            buf << ifs.rdbuf();

            std::string fileContents = buf.str();

            return Shader{fileContents, name};
        }, 
        "shader"
    );
}


auto AssetManager::load_mesh_from_memory(const std::string &name, MeshInfo meshInfo) -> MeshHandle {
    return load_with_cache<MeshView>(
        meshCache_,
        meshViews_,
        name,
        [&](void) -> std::optional<MeshView> {
            auto meshView = meshManager_->upload(meshInfo);
            return meshView;
        },
        "mesh"
    );
}


auto AssetManager::load_material_from_memory(const std::string &name, MaterialData matData) -> MaterialHandle {
    return load_with_cache<MaterialKey>(
        materialCache_,
        materialKeys_,
        name,
        [&](void) -> std::optional<MaterialKey> {
            auto matHandle = materialManager_->upload(matData);
            return matHandle;
        },
        "material"
    );
}


} // namespace NoctisEngine
