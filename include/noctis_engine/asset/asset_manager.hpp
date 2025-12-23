#pragma once
#include <filesystem>
#include <string_view>
#include <unordered_map>

#include "../core/assert.hpp"
#include "../rendering/texture.hpp"
#include "loading.hpp"

namespace NoctisEngine
{

constexpr std::string_view PNG_EXTENSION = ".png";
constexpr std::string_view JPEG_EXTENSION = ".jpeg";

class NCENG_API AssetManager {
public:
    AssetManager() = default;

    // If no name is passed, it will set the asset's name to the file name
    template <typename AssetType_>
    auto load_asset(const std::filesystem::path &path, const std::string &name = "") -> std::shared_ptr<AssetType_>;

private:
    std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> textureCache_;

    auto load_texture(const std::filesystem::path &path, const std::string &name) -> std::shared_ptr<Texture>;
};

template <typename AssetType_>
auto AssetManager::load_asset(const std::filesystem::path &path, const std::string &name) -> std::shared_ptr<AssetType_> {
    if (!std::filesystem::exists(path)) {
        Log::Error("{} does not exist", path.string());
        return nullptr;
    }

    const std::string extension = path.extension().string();
    const std::string filename = path.filename().string();

    if (extension == PNG_EXTENSION || extension == JPEG_EXTENSION) {
        if (!expect(
            std::is_same_v<AssetType_, Texture>, 
            "Asset path {} leads to an image and AssetType_ isn't a NoctisEngine::Texture", 
            path.string()))
            return nullptr;
        
        std::string realName = name.empty() ? path.stem().string() : name;
        return load_texture(path, realName);
    }

    Log::Error("{} This type of asset is not currently supported.", filename);
    return nullptr;
}

} // namespace NoctisEngine
