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
    Texture(TextureInfo texInfo);
    ~Texture();

    auto bind(int bindPoint, const Shader &shader) const -> void;

private:
    uint32_t texId_;
    std::string name_;
};

} // namespace NoctisEngine
