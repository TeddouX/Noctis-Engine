#include <asset/asset_manager.hpp>

namespace NoctisEngine
{

auto AssetManager::load_texture(
    const std::filesystem::path &path, 
    const std::string &name) -> std::shared_ptr<Texture> {

    const std::string filename = path.filename().string();

    auto it = textureCache_.find(path);
    if (it != textureCache_.end()) {
        Log::Debug("Loaded {} from cache", filename);
        return it->second;
    }

    std::shared_ptr<Texture> asset = Internal::load_texture(path, name);

    if (!asset) {
        Log::Error("Failed to load asset {}", filename);
        return nullptr;
    }

    Log::Debug("Successfully loaded asset {}", name);
    textureCache_.emplace(path, asset);

    return asset;
}

} // namespace NoctisEngine
