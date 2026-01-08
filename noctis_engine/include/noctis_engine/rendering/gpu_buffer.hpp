#pragma once
#include <stdint.h>
#include <string_view>
#include <span>
#include <vector>
#include <stdexcept>
#include <format>

#include "../noctis_engine.hpp"
#include "../core/exception.hpp"

namespace NoctisEngine
{

enum class BufferType {
    ARRAY_BUFFER,               // Vertex attributes
    ATOMIC_COUNTER_BUFFER,      // Atomic counter storage
    COPY_READ_BUFFER,           // Buffer copy source
    COPY_WRITE_BUFFER,          // Buffer copy destination
    DISPATCH_INDIRECT_BUFFER,   // Indirect compute dispatch commands
    DRAW_INDIRECT_BUFFER,       // Indirect command arguments
    ELEMENT_ARRAY_BUFFER,       // Vertex array indices
    PIXEL_PACK_BUFFER,          // Pixel read target
    PIXEL_UNPACK_BUFFER,        // Texture data source
    QUERY_BUFFER,               // Query result buffer
    SHADER_STORAGE_BUFFER,      // Read-write storage for shaders
    TEXTURE_BUFFER,             // Texture data buffer
    TRANSFORM_FEEDBACK_BUFFER,  // Transform feedback buffer
    UNIFORM_BUFFER,             // Uniform block storage
};

NCENG_API auto to_string(BufferType type) -> std::string;

// STREAM
// The data store contents will be modified once and used at most a few times.
// 
// STATIC
// The data store contents will be modified once and used many times.
// 
// DYNAMIC
// The data store contents will be modified repeatedly and used many times.
// 
// The nature of access may be one of these:
// 
// DRAW
// The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
// 
// READ
// The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
// 
// COPY
// The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
enum class WriteType : uint8_t {
    STREAM_DRAW,
    STREAM_READ,
    STREAM_COPY,

    STATIC_DRAW,
    STATIC_READ,
    STATIC_COPY,

    DYNAMIC_DRAW,
    DYNAMIC_READ,
    DYNAMIC_COPY
};

using CPUBufferView = const std::span<const std::byte>;

class NCENG_API GPUBuffer {
public:
    GPUBuffer() = default;
    GPUBuffer(size_t size, std::string_view name);

    auto write(CPUBufferView data, size_t offset, WriteType type) const -> void;
    auto size() const -> size_t;
    auto name() const -> std::string_view;

    auto bind_as(BufferType type) const -> void;
    auto bind_buffer_base(BufferType type, uint32_t bindPoint) const -> void;
    auto bind_buffer_range(BufferType type, uint32_t bindPoint, size_t offset, size_t size) const -> void;

private:
    uint32_t id_{};
    size_t size_{};
};

template <typename T>
auto resize_buffer(GPUBuffer &buf, const std::vector<T> &cpuBuf) -> void {
    size_t cpuBufSize = cpuBuf.size() * sizeof(T);

    if (cpuBufSize >= buf.size()) {
        size_t newBufSize = buf.size() * 2;
        while (newBufSize < cpuBufSize)
            newBufSize *= 2;

        buf = GPUBuffer(newBufSize, buf.name());
    }
}

template <typename T>
auto get_cpu_buffer_view(const std::vector<T> &buf, size_t offset, size_t size) -> CPUBufferView {
    if (size + offset > buf.size())
        throw Exception(
            "Can't create cpu buffer view, invalid offset and/or size (off {} + size {} > buf {}).", 
            offset, size, buf.size()
        );

    return std::as_bytes(std::span{buf.data() + offset, size});
}

template <typename T>
auto get_cpu_buffer_view(const T &val) -> CPUBufferView {
    return std::as_bytes(std::span{std::addressof(val), 1});
}

} // namespace NoctisEngine
