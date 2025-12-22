#pragma once
#include <filesystem>
#include <string_view>
#include <unordered_map>

#include <stb/stb_image.h>

#include "../core/assert.hpp"
#include "../rendering/texture.hpp"
#include "loading.hpp"

namespace NoctisEngine
{

constexpr std::string_view PNG_EXTENSION = ".png";
constexpr std::string_view JPEG_EXTENSION = ".jpeg";

class AssetManager {
public:
    AssetManager() = default;

    template <typename AssetType_>
    std::shared_ptr<AssetType_> load_asset(const std::filesystem::path &path);

private:
    std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> textureCache_;
};

template <typename AssetType_>
std::shared_ptr<AssetType_> AssetManager::load_asset(const std::filesystem::path &path) {
    std::string extension = path.extension().string();
    std::string filename = path.filename().string();

    if (extension == PNG_EXTENSION || extension == JPEG_EXTENSION) {
        if (!expect(
            std::is_same_v<AssetType_, Texture>, 
            "Asset path {} leads to an image and AssetType_ isn't a NoctisEngine::Texture", 
            path.string()))
            return nullptr;

        auto it = textureCache_.find(path);
        if (it != textureCache_.end()) {
            Log::Debug("Loaded {} from cache", filename);
            return it->second;
        }

        std::shared_ptr<Texture> asset = Internal::load_texture(path);

        if (!asset) {
            Log::Error("Failed to load asset {}", filename);
            return nullptr;
        }

        Log::Debug("Successfully loaded asset {}", filename);

        return asset;
    }

    Log::Error("{} This type of asset is not currently supported.", filename);
    return nullptr;
}

} // namespace NoctisEngine
