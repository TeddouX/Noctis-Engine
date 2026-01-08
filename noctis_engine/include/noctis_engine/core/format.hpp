#pragma once
#include <concepts>
#include <format>
#include <string>

// Copied from: https://github.com/nathan-baggs/ufps/tree/main/src/utils/formatter.h
// License: https://github.com/nathan-baggs/ufps/tree/main/LICENSE

namespace NoctisEngine::Internal
{
 
template <class T>
concept HasToStringMember = requires(T a) {
    { a.to_string() } -> std::convertible_to<std::string>;
};

template <class T>
concept HasToStringFree = requires(T a) {
    { to_string(a) } -> std::convertible_to<std::string>;
};


struct ToStringCPO {
    template <HasToStringMember T>
    std::string operator()(T&& obj) const { return obj.to_string(); }

    template <class T>
        requires(!HasToStringMember<T> && HasToStringFree<T>)
    std::string operator()(T&& obj) const { return to_string(obj); } // ADL works
};

inline constexpr auto to_string = ToStringCPO{};

template <class T>
struct Formatter
{
    constexpr auto parse(std::format_parse_context &ctx) {
        return std::ranges::begin(ctx);
    }

    auto format(const T &obj, std::format_context &ctx) const {
        return std::format_to(ctx.out(), "{}", Internal::to_string(obj));
    }
};

} // namespace NoctisEngine::Internal

template <class T>
concept CanFormat = requires(T a) {
    { NoctisEngine::Internal::to_string(a) } -> std::convertible_to<std::string>;
};

template <CanFormat T>
struct std::formatter<T> : NoctisEngine::Internal::Formatter<T>
{};
