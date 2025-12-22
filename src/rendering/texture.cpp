#include <rendering/texture.hpp>

#include <glad/glad.h>

#include <core/assert.hpp>

namespace NoctisEngine
{
    
Texture::Texture(TextureInfo texInfo)
    : name_(texInfo.name)
{
    ::glGenTextures(1, &texId_);

    if (!expect(texId_ >= 0, "Texture failed to generate"))
        return;

    ::glBindTexture(GL_TEXTURE_2D, texId_);

    // TODO: make this controllable
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum internalFormat = GL_RGBA8;
    GLenum dataFormat = GL_RGBA;

    if (texInfo.nrChannels == 1)
    {
        internalFormat = GL_R8;
        dataFormat = GL_RED;
    }
    else if (texInfo.nrChannels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

	::glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		internalFormat, 
		texInfo.width, 
		texInfo.height, 
		0, 
		dataFormat,
		GL_UNSIGNED_BYTE, 
		texInfo.data
	);

	::glGenerateMipmap(GL_TEXTURE_2D);

    ::glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    ::glDeleteTextures(1, &texId_);
}

auto Texture::bind(int bindPoint, const Shader &shader) const -> void {
    ::glActiveTexture(GL_TEXTURE0 + bindPoint);
    ::glBindTexture(GL_TEXTURE_2D, texId_);
}

} // namespace NoctisEngine
