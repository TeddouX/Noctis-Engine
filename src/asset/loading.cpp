#include <asset/loading.hpp>

#include <stb/stb_image.h>

#include <core/logging.hpp>

namespace NoctisEngine::Internal
{
    
NCENG_API std::optional<Texture> load_texture(const std::filesystem::path &path, const std::string &name) {
    int width, height;
    int nrChannels;

    if (!std::filesystem::exists(path)) {
        Log::Error("{} does not exist.", path.string());
        return std::nullopt;
    }

    uint8_t *data = ::stbi_load(
        path.string().c_str(), 
        &width, &height, 
        &nrChannels, 0
    );

    if (!data) {
        Log::Error("Failed to load image {}: {}", path.string(), ::stbi_failure_reason());
        return std::nullopt;
    }

    TextureInfo texInfo {
        .data = data,
        .width = width, .height = height,
        .nrChannels = nrChannels,
        .name = name
    };

    Texture tex{texInfo};

    ::stbi_image_free(data);

    return tex;
}

} // namespace NoctisEngine::Internal
