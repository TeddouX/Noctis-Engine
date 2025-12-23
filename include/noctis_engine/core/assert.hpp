#pragma once
#include <format>
#include <stacktrace>

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

// Expect will not quit the application
template <class... Args>
constexpr auto expect(bool predicate, std::format_string<Args...> msg, Args &&...args) -> bool {
    if (!predicate) {
        Log::Error("Expect failed: {}", std::format(msg, std::forward<Args>(args)...));
        Log::Error("Expect failed: {}", std::stacktrace::current(1));
    }
    
    return predicate;
}

} // namespace NoctisEngine

