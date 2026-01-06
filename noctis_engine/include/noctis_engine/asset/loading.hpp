#pragma once
#include <optional>
#include <filesystem>

#include "../rendering/texture.hpp"
#include "../noctis_engine.hpp"

namespace NoctisEngine::Internal
{

NCENG_API std::optional<Texture> load_texture(const std::filesystem::path &path, const std::string &name);

} // namespace NoctisEngine::Internal
