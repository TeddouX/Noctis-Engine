#include <rendering/bindless_texture.hpp>

#include <glad/gl.h>

namespace NoctisEngine
{
    
BindlessTexture::BindlessTexture(Texture tex) {
    handle_ = glGetTextureHandleARB(tex.gl_handle());
}

auto BindlessTexture::make_resident(bool b) const -> void {
    if (b) glMakeTextureHandleResidentARB(handle_);
    else   glMakeTextureHandleNonResidentARB(handle_);
}

auto BindlessTexture::get_handle() const -> std::uint64_t {
    return handle_;
}

} // namespace NoctisEngine
