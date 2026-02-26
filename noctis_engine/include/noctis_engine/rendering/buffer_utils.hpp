#pragma once
#include "gpu_buffer.hpp"

namespace NoctisEngine
{
    
template <typename T>
auto resize_buffer(GPUBuffer &buf, const std::vector<T> &cpuBuf) -> bool {
    size_t cpuBufSize = cpuBuf.size() * sizeof(T);

    if (buf.size() >= cpuBufSize) 
        return false;

    size_t newBufSize = std::max(buf.size() * 2, 1zu);
    while (newBufSize < cpuBufSize)
        newBufSize *= 2;
    
    Log::Info("Resizing buffer '{}', {} => {}", buf.get_name(), buf.size(), newBufSize);
    buf.delete_gpu();
    buf = GPUBuffer{newBufSize, buf.get_name()};
            
    return true;
}

template <typename T>
auto get_cpu_buffer_view(const std::vector<T> &buf, size_t offset, size_t size) -> CPUBufferReadView {
    if (size + offset > buf.size())
        throw Exception(
            "Can't create cpu buffer view, invalid offset and/or size (off {} + size {} > buf {}).", 
            offset, size, buf.size()
        );

    return std::as_bytes(std::span{buf.data() + offset, size});
}

template <typename T>
auto get_cpu_buffer_view(const T &val) -> CPUBufferReadView {
    return std::as_bytes(std::span{std::addressof(val), 1});
}

template <typename T>
auto get_cpu_buffer_view(T &val) -> CPUBufferWriteView {
    return std::as_writable_bytes(std::span{std::addressof(val), 1});
}

} // namespace NoctisEngine
