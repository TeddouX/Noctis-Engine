#include <asset/asset_manager.hpp>

#include <fstream>
#include <functional>

namespace NoctisEngine
{

template <typename AssetType_>
auto load_with_cache(
    std::unordered_map<std::filesystem::path, std::shared_ptr<AssetType_>> &cache,
    const std::filesystem::path &path,
    const std::string &name,
    std::function<std::shared_ptr<AssetType_> (void)> loader,
    std::string_view assetKind) -> std::shared_ptr<AssetType_> {

    const std::string filename = path.filename().string();

    if (auto it = cache.find(path); it != cache.end()) {
        Log::Debug("Loaded {} '{}' from cache", assetKind, filename);
        return it->second;
    }

    auto asset = loader();
    if (!asset) {
        Log::Error("Failed to load {} '{}'", assetKind, filename);
        return nullptr;
    }

    Log::Debug("Successfully loaded {} '{}'", assetKind, name);
    cache.emplace(path, asset);

    return asset;
}

auto AssetManager::load_texture(
    const std::filesystem::path &path, 
    const std::string &name) -> std::shared_ptr<Texture> {

    return load_with_cache<Texture>(
        textureCache_, 
        path, 
        name, 
        [&] -> std::shared_ptr<Texture> { 
            return Internal::load_texture(path, name); 
        }, 
        "texture"
    );
}

auto AssetManager::load_shader(
    const std::filesystem::path &path, 
    const std::string &name) -> std::shared_ptr<Shader> {

    return load_with_cache<Shader>(
        shaderCache_, 
        path, 
        name, 
        [&] -> std::shared_ptr<Shader> { 
            std::ifstream ifs;

            std::stringstream buf;
            ifs.open(path);
            buf << ifs.rdbuf();

            std::string fileContents = buf.str();

            return std::make_shared<Shader>(fileContents, name);
        }, 
        "shader"
    );
}


} // namespace NoctisEngine
