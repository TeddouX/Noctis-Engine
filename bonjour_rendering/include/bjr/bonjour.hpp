#pragma once
#include <expected>

namespace Bjr
{

template <typename T, typename E>
using Err = std::expected<T, E>;
    
} // namespace Bjr
