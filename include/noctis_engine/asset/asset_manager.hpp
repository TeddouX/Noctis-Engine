#pragma once
#include <filesystem>
#include <string_view>
#include <unordered_map>

#include "../core/assert.hpp"
#include "../rendering/texture.hpp"
#include "../rendering/shader.hpp"
#include "loading.hpp"

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
    auto load_asset(const std::filesystem::path &path, const std::string &name = "") -> std::shared_ptr<AssetType_>;

private:
    std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> textureCache_;
    std::unordered_map<std::filesystem::path, std::shared_ptr<Shader>>  shaderCache_;

    auto load_texture(const std::filesystem::path &path, const std::string &name) -> std::shared_ptr<Texture>;
    auto load_shader(const std::filesystem::path &path, const std::string &name) -> std::shared_ptr<Shader>;
};

template <typename AssetType_>
auto AssetManager::load_asset(const std::filesystem::path &path, const std::string &name) -> std::shared_ptr<AssetType_> {
    if (!std::filesystem::exists(path)) {
        Log::Error("{} does not exist", path.string());
        return nullptr;
    }

    const std::string extension = path.extension().string();
    const std::string filename = path.filename().string();
    const std::string realName = name.empty() ? path.stem().string() : name;

    if constexpr (std::is_same_v<AssetType_, Texture>) {
        if (extension != PNG_EXTENSION && extension != JPEG_EXTENSION) {
            Log::Error("{} is not an image", path.string());
            return nullptr;
        }

        return load_texture(path, realName);
    }
    else if constexpr (std::is_same_v<AssetType_, Shader>) {
        if (extension != GLSL_EXTENSION) {
            Log::Error("{} is not a shader", path.string());
            return nullptr;
        }

        return load_shader(path, realName);
    }
    else {
        static_assert(false, "Unsupported AssetType_ passed to AssetManager::load_asset");
        return nullptr;
    }
}

} // namespace NoctisEngine
