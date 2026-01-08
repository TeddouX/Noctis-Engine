#pragma once
#include <stdexcept>
#include <format>
#include <string>
#include <stacktrace>

#include "format.hpp"

namespace NoctisEngine
{
 
class Exception : public std::runtime_error {
public:
    template <typename... Args>
    Exception(std::format_string<Args...> fmt, Args &&...args)
        : std::runtime_error(std::format(fmt, std::forward<Args>(args)...))
        , what_(std::format("{}\nStacktrace:\n{}", std::runtime_error::what(), std::stacktrace::current(1)))
    {}

    auto to_string() const -> const std::string & {
        return what_;
    }

    auto what() const noexcept -> const char * override {
        return what_.c_str();
    }

private:
    std::string what_;
};

} // namespace NoctisEngine
