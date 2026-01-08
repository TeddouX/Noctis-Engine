#pragma once
#include <format>
#include <print>
#include <source_location>
#include <string_view>
#include <chrono>
#include <filesystem>

#include "format.hpp"

namespace NoctisEngine
{
    
enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    CRITICAL,
};

inline auto to_string(LogLevel level) -> std::string {
    switch (level) {
        using enum LogLevel;
        case DEBUG:     return "DEBUG"; 
        case INFO:      return "INFO"; 
        case WARN:      return "WARN"; 
        case ERROR:     return "ERROR"; 
        case CRITICAL:  return "CRITICAL";
        default:        return "?";
    }
}

class Log {
public:
    template <typename... Args>
    static auto Debug(std::format_string<Args...> fmt, Args &&...args) {
        log(LogLevel::DEBUG, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static auto Info(std::format_string<Args...> fmt, Args &&...args) {
        log(LogLevel::INFO, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static auto Warn(std::format_string<Args...> fmt, Args &&...args) {
        log(LogLevel::WARN, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static auto Error(std::format_string<Args...> fmt, Args &&...args) {
        log(LogLevel::ERROR, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static auto Critical(std::format_string<Args...> fmt, Args &&...args) {
        log(LogLevel::CRITICAL, fmt, std::forward<Args>(args)...);
    }

private:
    template <typename... Args>
    static auto log(LogLevel level, std::format_string<Args...> fmt, Args &&...args) -> void {
        auto timeStr = get_time_string();

        std::string formattedMsg = std::format(fmt, std::forward<Args>(args)...);

        constexpr std::string_view formatStr = "[{} {}]: {}";
        std::println(formatStr, 
            level,
            timeStr,
            formattedMsg
        );
    }

    static auto get_time_string() -> std::string {
        using namespace std::chrono;

        system_clock::time_point now = system_clock::now();
        // Time zone offset
        seconds offset = current_zone()->get_info(now).offset;
        duration sysTime = now.time_since_epoch() + offset;

        int64_t s = duration_cast<seconds>(sysTime).count() % 60;
        int64_t m = duration_cast<minutes>(sysTime).count() % 60;
        int64_t h = duration_cast<hours>(sysTime).count()   % 24;

        return std::format("{:02}:{:02}:{:02}", h, m, s);
    }
};

} // namespace NoctisEngine

