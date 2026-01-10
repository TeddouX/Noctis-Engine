#pragma once
#include <stdint.h>

#include "../noctis_engine.hpp"
#include "math.hpp"

namespace NoctisEngine
{
    
class Color {
public:
    Color() = default;
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : m_r(red), m_g(green), m_b(blue), m_a(alpha) {}

    static const Color BLACK;

    constexpr auto red() const -> uint8_t { return m_r; }
    constexpr auto green() const -> uint8_t { return m_g; }
    constexpr auto blue() const -> uint8_t { return m_b; }
    constexpr auto alpha() const -> uint8_t { return m_a; }

    constexpr auto red_f() const -> float { return m_r / 255; }
    constexpr auto green_f() const -> float { return m_g / 255; }
    constexpr auto blue_f() const -> float { return m_b / 255; }
    constexpr auto alpha_f() const -> float { return m_a / 255; }

    constexpr auto to_floats() const -> glm::vec4 { 
        return glm::vec4{red_f(), green_f(), blue_f(), alpha_f()};
    }

private:
    uint8_t m_r{}, m_g{}, m_b{}, m_a{};
};

inline const Color Color::BLACK{0, 0, 0, 255};

} // namespace NoctisEngine

