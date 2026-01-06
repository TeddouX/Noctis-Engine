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
    std::unordered_map<std::filesystem::path, AssetHandle<AssetType_>> &cache,
    std::vector<AssetType_> &storage,
    const std::filesystem::path &path,
    const std::string &name,
    std::function<std::optional<AssetType_> (void)> loader,
    std::string_view assetKind) -> AssetHandle<AssetType_> {

    const std::string filename = path.filename().string();

    if (auto it = cache.find(path); it != cache.end()) {
        Log::Debug("Loaded {} '{}' from cache", assetKind, filename);
        return it->second;
    }

    std::optional<AssetType_> asset = loader();
    if (!asset) {
        Log::Error("Failed to load {} '{}'", assetKind, filename);
        return AssetHandle<AssetType_>{};
    }

    Log::Debug("Successfully loaded {} '{}'", assetKind, name);

    auto handle = create_handle(storage, asset.value());
    cache.emplace(path, handle);

    return handle;
}

auto AssetManager::load_texture(
    const std::filesystem::path &path, 
    const std::string &name) -> TextureHandle {

    return load_with_cache<Texture>(
        textureCache_,
        textures_,
        path, 
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
        path, 
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


} // namespace NoctisEngine
