#pragma once
#include <stdint.h>
#include <string_view>
#include <span>
#include <vector>
#include <stdexcept>
#include <format>

#include "../noctis_engine.hpp"
#include "../core/exception.hpp"
#include "../core/logging.hpp"

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

enum class BufferFlag : std::uint32_t {
    MAP_READ_BIT = 0x0001,
    MAP_WRITE_BIT = 0x0002,
    MAP_PERSISTENT_BIT = 0x0040,
    MAP_COHERENT_BIT = 0x0080,
    DYNAMIC_STORAGE_BIT = 0x0100,
    CLIENT_STORAGE_BIT = 0x0200
};

NCENG_API auto to_string(BufferType type) -> std::string;

using CPUBufferView = const std::span<std::byte>;

class NCENG_API GPUBuffer {
public:
    GPUBuffer() = default;
    GPUBuffer(size_t size, std::string_view name, BufferFlag flags = BufferFlag::DYNAMIC_STORAGE_BIT);

    auto copy_to(GPUBuffer &other) -> void;
    auto write(CPUBufferView data, size_t offset) const -> void;
    auto size() const -> size_t;
    auto gl_handle() const -> std::uint32_t;

    auto delete_gpu() -> void;

    auto bind_as(BufferType type) const -> void;
    auto bind_buffer_base(BufferType type, uint32_t bindPoint) const -> void;
    auto bind_buffer_range(BufferType type, uint32_t bindPoint, size_t offset, size_t size) const -> void;

    auto map(bool readable) -> void;
    auto unmap() -> void;
    auto mapped_write(CPUBufferView data, size_t offset) -> void;

    auto get_data(std::size_t offset, CPUBufferView &data) const -> void;

private:
    uint32_t id_{};
    size_t   size_{};
    void     *map_;
};

struct GPUBufferBlock {
    std::size_t offset;
    std::size_t size;
};

template <typename T>
auto resize_buffer(GPUBuffer &buf, const std::vector<T> &cpuBuf, std::string_view name) -> void {
    size_t cpuBufSize = cpuBuf.size() * sizeof(T);

    if (buf.size() < cpuBufSize) {
        size_t newBufSize = std::max(buf.size() * 2, 1zu);
        while (newBufSize < cpuBufSize)
            newBufSize *= 2;

        Log::Info("Resizing buffer {}, {} => {}", name, buf.size(), newBufSize);

        buf.delete_gpu();
        buf = GPUBuffer{newBufSize, name};
    }
}

inline auto copy_resize_buffer(GPUBuffer &buf, size_t requiredSize, std::string_view name) -> bool {
    if (buf.size() >= requiredSize)
        return false;

    size_t newBufSize = std::max(buf.size() * 2, 1zu);
    while (newBufSize < requiredSize)
        newBufSize *= 2;

    Log::Info("Resizing buffer '{}', {} bytes => {} bytes", name, buf.size(), newBufSize);

    GPUBuffer temp{newBufSize, name};
    buf.copy_to(temp);
    buf.delete_gpu();
    buf = temp;

    return true;
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
