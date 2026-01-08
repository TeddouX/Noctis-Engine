#pragma once
#include <format>
#include <stacktrace>
#include <utility>

#include "logging.hpp"

namespace NoctisEngine
{
    
template <class... Args>
constexpr auto ensure(bool predicate, std::format_string<Args...> msg, Args &&...args) -> void {
    if (!predicate) {
        Log::Critical("{}", std::format(msg, std::forward<Args>(args)...));
        Log::Critical("{}", std::stacktrace::current(1));
        
        std::terminate();
        std::unreachable();
    }
}

} // namespace NoctisEngine

