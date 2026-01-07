#pragma once
#include <format>
#include <print>
#include <source_location>
#include <string_view>
#include <chrono>
#include <filesystem>

namespace NoctisEngine
{
    
enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    CRITICAL,
};

template <LogLevel level, class... Args>
class Logger {
public:
    Logger(std::format_string<Args...> msg, Args &&...args, std::source_location loc = std::source_location::current()) {
        auto timeStr = get_time_string();
        auto debugLvlStr = debug_lvl_to_str();

        std::string formattedMsg = std::format(msg, std::forward<Args>(args)...);

        constexpr std::string_view formatStr = "[{} {}] in {}({}:{}): {}";
        const std::filesystem::path filePath(loc.file_name());

        std::println(formatStr, 
            debugLvlStr,
            timeStr,
            filePath.filename().string(), loc.line(), loc.column(),
            formattedMsg
        );
    }

private:
    auto get_time_string() -> std::string {
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

    auto debug_lvl_to_str() -> std::string {
        if constexpr (level == LogLevel::DEBUG)         return "DEBUG";
        else if constexpr (level == LogLevel::INFO)     return "INFO";
        else if constexpr (level == LogLevel::WARN)     return "WARN";
        else if constexpr (level == LogLevel::ERROR)    return "ERROR";
        else if constexpr (level == LogLevel::CRITICAL) return "CRITICAL";
        else return "?";
    }
};

template <LogLevel level, class... Args>
Logger(std::format_string<Args...>, Args &&...) -> Logger<level, Args...>;

namespace Log
{
    
template <typename... Args>
using Debug = Logger<LogLevel::DEBUG, Args...>;

template <typename... Args>
using Info = Logger<LogLevel::INFO, Args...>;

template <typename... Args>
using Warn = Logger<LogLevel::WARN, Args...>;

template <typename... Args>
using Error = Logger<LogLevel::ERROR, Args...>;

// After a critical message is logged, the application should quit
template <typename... Args>
using Critical = Logger<LogLevel::CRITICAL, Args...>;

} // namespace Log

} // namespace NoctisEngine

