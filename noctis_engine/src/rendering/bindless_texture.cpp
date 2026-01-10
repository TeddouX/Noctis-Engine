#include <rendering/bindless_texture.hpp>

#include <glad/gl.h>

#include <core/exception.hpp>

namespace NoctisEngine
{
    
BindlessTexture::BindlessTexture(Texture tex) {
    handle_ = glGetTextureHandleARB(tex.gl_handle());

    if (handle_ == 0)
        throw Exception("Failed to get a handle to a texture.");

    make_resident(true);
}

auto BindlessTexture::make_resident(bool b) const -> void {
    if (b) glMakeTextureHandleResidentARB(handle_);
    else   glMakeTextureHandleNonResidentARB(handle_);
}

auto BindlessTexture::get_handle() const -> std::uint64_t {
    return handle_;
}

} // namespace NoctisEngine
