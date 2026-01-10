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

using CPUBufferReadView = const std::span<const std::byte>;
using CPUBufferWriteView = std::span<std::byte>;

class NCENG_API GPUBuffer {
public:
    GPUBuffer() = default;
    GPUBuffer(size_t size, std::string_view name, BufferFlag flags = BufferFlag::DYNAMIC_STORAGE_BIT);

    auto copy_to(GPUBuffer &other) -> void;
    auto write(CPUBufferReadView data, size_t offset) const -> void;
    auto size() const -> size_t;
    auto gl_handle() const -> std::uint32_t;

    auto delete_gpu() -> void;

    auto bind_as(BufferType type) const -> void;
    auto bind_buffer_base(BufferType type, uint32_t bindPoint) const -> void;
    auto bind_buffer_range(BufferType type, uint32_t bindPoint, size_t offset, size_t size) const -> void;

    auto map(bool readable) -> void;
    auto unmap() -> void;
    auto mapped_write(CPUBufferReadView data, size_t offset) -> void;

    auto get_data(std::size_t offset, CPUBufferWriteView data) const -> void;

private:
    uint32_t id_{};
    size_t   size_{};
    void     *map_ = nullptr;
};

struct GPUBufferBlock {
    std::size_t offset;
    std::size_t size;
};

} // namespace NoctisEngine
