#pragma once
#include <memory>
#include <filesystem>

#include "../rendering/texture.hpp"
#include "../noctis_engine.hpp"

namespace NoctisEngine::Internal
{

NCENG_API std::unique_ptr<Texture> load_texture(const std::filesystem::path &path);

} // namespace NoctisEngine::Internal
