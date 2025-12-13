#pragma once
#include <expected>
#include <string>
#include <optional>

namespace Bjr
{
    
template <typename T, typename E>
using ValueErr = std::expected<T, E>;

using Err = std::optional<std::string>;

inline static Err noerr{};

} // namespace Bjr
