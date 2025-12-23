#include <asset/loading.hpp>

#include <stb/stb_image.h>

#include <core/logging.hpp>

namespace NoctisEngine::Internal
{
    
NCENG_API std::unique_ptr<Texture> load_texture(const std::filesystem::path &path, const std::string &name) {
    int width, height;
    int nrChannels;

    if (!std::filesystem::exists(path)) {
        Log::Error("{} does not exist.", path.string());
        return nullptr;
    }

    uint8_t *data = ::stbi_load(
        path.string().c_str(), 
        &width, &height, 
        &nrChannels, 0
    );

    if (!data) {
        Log::Error("Failed to load image {}: {}", path.string(), ::stbi_failure_reason());
        return nullptr;
    }

    TextureInfo texInfo {
        .data = data,
        .width = width, .height = height,
        .nrChannels = nrChannels,
        .name = name
    };

    auto tex = std::make_unique<Texture>(texInfo);

    ::stbi_image_free(data);

    return std::move(tex);
}

} // namespace NoctisEngine::Internal
