#include <noctis_engine/rendering/gpu_buffer.hpp>

#include <stdexcept>
#include <format>

#include <glad/gl.h>

#include <core/exception.hpp>
#include <core/logging.hpp>
#include <core/format.hpp>
#include <math/math.hpp>

namespace NoctisEngine
{
    
static auto opengl_buffer_type(BufferType type) -> GLenum;
static auto is_bindable_to_index(BufferType type) -> bool;

GPUBuffer::GPUBuffer(size_t size, std::string_view name, BufferFlag flags)
    : size_(size)
{
    glCreateBuffers(1, &id_);
    glNamedBufferStorage(id_, size, nullptr, static_cast<GLbitfield>(flags));
    glObjectLabel(GL_BUFFER, id_, name.size(), name.data());
}

auto GPUBuffer::write(CPUBufferView data, size_t offset) const -> void {
    if (offset + data.size_bytes() > size_)
        throw Exception(
            "Tried to write {} bytes at offset {} into a buffer that is {} bytes long.", 
            data.size_bytes(), offset, size_
        );

    glNamedBufferSubData(id_, offset, data.size_bytes(), data.data());
}

auto GPUBuffer::copy_to(GPUBuffer &other) -> void {
    if (size_ > other.size_)
        throw Exception(
            "Tried copying from a buffer that is {} bytes long to a buffer that is {} bytes long",
            size_, other.size_
        );

    glCopyNamedBufferSubData(id_, other.id_, 0, 0, size_);
}

auto GPUBuffer::bind_as(BufferType type) const -> void {
    glBindBuffer(opengl_buffer_type(type), id_);
}

auto GPUBuffer::bind_buffer_base(BufferType type, uint32_t bindPoint) const -> void {
    if (!is_bindable_to_index(type))
        throw Exception("BufferType '{}' is not bindable to an index.", type);

    glBindBufferBase(opengl_buffer_type(type), bindPoint, id_);
}

auto GPUBuffer::bind_buffer_range(BufferType type, uint32_t bindPoint, size_t offset, size_t size) const -> void {
    if (!is_bindable_to_index(type))
        throw Exception("BufferType '{}' is not bindable to an index.", type);

    if (offset + size > size_)
        throw Exception(
            "Failed to bind buffer range at offset {} with length {} because it exceeds the buffer's size ({})" ,
            size, offset, size_
        );

    glBindBufferRange(opengl_buffer_type(type), bindPoint, id_, offset, size);
}

auto GPUBuffer::size() const -> size_t {
    return size_;
}

auto GPUBuffer::gl_handle() const -> std::uint32_t {
    return id_;
}

auto GPUBuffer::delete_gpu() -> void {
    if (map_)
        glUnmapNamedBuffer(id_);
    glDeleteBuffers(1, &id_);
}

auto GPUBuffer::map(bool readable) -> void {
    map_ = glMapNamedBuffer(id_, readable ? GL_READ_WRITE : GL_WRITE_ONLY);
    if (!map_)
        throw Exception("Failed to map buffer.");
}

auto GPUBuffer::unmap() -> void {
    glUnmapNamedBuffer(id_);
}

auto GPUBuffer::mapped_write(CPUBufferView data, size_t offset) -> void {
    if (offset + data.size_bytes() > size_)
        throw Exception(
            "Failed to mapped_write {} bytes at offset {} into a buffer that is {} bytes long." ,
            data.size_bytes(), offset, size_
        );

    if (!map_) {
        Log::Warn("Tried to call GPUBuffer::mapped_write to an unmmapped buffer.");
        return;
    }

    std::memcpy(map_ + offset, data.data(), data.size_bytes());
}


NCENG_API auto to_string(BufferType type) -> std::string {
    switch (type) {
        using enum BufferType;
        case ARRAY_BUFFER:              return "ARRAY_BUFFER"; 
        case ATOMIC_COUNTER_BUFFER:     return "ATOMIC_COUNTER_BUFFER"; 
        case COPY_READ_BUFFER:          return "COPY_READ_BUFFER"; 
        case COPY_WRITE_BUFFER:         return "COPY_WRITE_BUFFER"; 
        case DISPATCH_INDIRECT_BUFFER:  return "DISPATCH_INDIRECT_BUFFER"; 
        case DRAW_INDIRECT_BUFFER:      return "DRAW_INDIRECT_BUFFER"; 
        case ELEMENT_ARRAY_BUFFER:      return "ELEMENT_ARRAY_BUFFER"; 
        case PIXEL_PACK_BUFFER:         return "PIXEL_PACK_BUFFER"; 
        case PIXEL_UNPACK_BUFFER:       return "PIXEL_UNPACK_BUFFER"; 
        case QUERY_BUFFER:              return "QUERY_BUFFER"; 
        case SHADER_STORAGE_BUFFER:     return "SHADER_STORAGE_BUFFER"; 
        case TEXTURE_BUFFER:            return "TEXTURE_BUFFER"; 
        case TRANSFORM_FEEDBACK_BUFFER: return "TRANSFORM_FEEDBACK_BUFFER"; 
        case UNIFORM_BUFFER:            return "UNIFORM_BUFFER";
        default:
            throw Exception("Unsupported BufferType: {}", static_cast<int>(type));
    }
}

auto opengl_buffer_type(BufferType type) -> GLenum {
    switch (type) {
        using enum BufferType;
        case ARRAY_BUFFER:              return GL_ARRAY_BUFFER; 
        case ATOMIC_COUNTER_BUFFER:     return GL_ATOMIC_COUNTER_BUFFER; 
        case COPY_READ_BUFFER:          return GL_COPY_READ_BUFFER; 
        case COPY_WRITE_BUFFER:         return GL_COPY_WRITE_BUFFER; 
        case DISPATCH_INDIRECT_BUFFER:  return GL_DISPATCH_INDIRECT_BUFFER; 
        case DRAW_INDIRECT_BUFFER:      return GL_DRAW_INDIRECT_BUFFER; 
        case ELEMENT_ARRAY_BUFFER:      return GL_ELEMENT_ARRAY_BUFFER; 
        case PIXEL_PACK_BUFFER:         return GL_PIXEL_PACK_BUFFER; 
        case PIXEL_UNPACK_BUFFER:       return GL_PIXEL_UNPACK_BUFFER; 
        case QUERY_BUFFER:              return GL_QUERY_BUFFER; 
        case SHADER_STORAGE_BUFFER:     return GL_SHADER_STORAGE_BUFFER; 
        case TEXTURE_BUFFER:            return GL_TEXTURE_BUFFER; 
        case TRANSFORM_FEEDBACK_BUFFER: return GL_TRANSFORM_FEEDBACK_BUFFER; 
        case UNIFORM_BUFFER:            return GL_UNIFORM_BUFFER;
        default:
            throw Exception("Unsupported BufferType: {}", static_cast<int>(type));
    }
}

auto is_bindable_to_index(BufferType type) -> bool {
    switch (type) {
        using enum BufferType;
        case ATOMIC_COUNTER_BUFFER:
        case SHADER_STORAGE_BUFFER:
        case TRANSFORM_FEEDBACK_BUFFER:
        case UNIFORM_BUFFER:
            return true;
        
        default:
            return false;
    }
}

} // namespace NoctisEngine
