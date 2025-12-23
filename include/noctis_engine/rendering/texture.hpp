#pragma once
#include <stdint.h>
#include <string>

#include "../noctis_engine.hpp"
#include "shader.hpp"

namespace NoctisEngine
{
    
struct TextureInfo {
    uint8_t *data;
    int width, height;
    int nrChannels;
    std::string name;
};

class NCENG_API Texture {
public:
    enum class MinifyingFunction : uint32_t {
        NEAREST = 0x2600,
        LINEAR = 0x2601,
        NEAREST_MIPMAP_NEAREST = 0x2700,
        LINEAR_MIPMAP_NEAREST = 0x2701,
        NEAREST_MIPMAP_LINEAR = 0x2702,
        LINEAR_MIPMAP_LINEAR = 0x2703,
    };

    enum class MagnifyingFunction : uint32_t {
        NEAREST = 0x2600,
        LINEAR = 0x2600,
    };

    enum class WrapParam : uint32_t {
        CLAMP_TO_EDGE = 0x812F,
        CLAMP_TO_BORDER = 0x812D,
        MIRRORED_REPEAT = 0x8370,
        REPEAT = 0x2901,
        MIRROR_CLAMP_TO_EDGE = 0x8743,
    };

    Texture(TextureInfo texInfo);
    ~Texture();

    // The shader must be bound before calling this function!!
    auto bind(int bindPoint, const Shader &shader) const -> void;

    auto set_min_function(MinifyingFunction param) const -> void;
    auto set_mag_function(MagnifyingFunction param) const -> void;
    auto set_wrap_function(WrapParam paramU, WrapParam paramV) const -> void;

private:
    uint32_t texId_;
    std::string name_;
};

} // namespace NoctisEngine
