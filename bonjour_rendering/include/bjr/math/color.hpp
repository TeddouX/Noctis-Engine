#pragma once
#include <stdint.h>

namespace Bjr
{
    
class Color {
public:
    Color() = default;
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : m_r(red), m_g(green), m_b(blue), m_a(alpha) {}

    static const Color BLACK;

    constexpr uint8_t red() const { return m_r; }
    constexpr uint8_t green() const { return m_g; }
    constexpr uint8_t blue() const { return m_b; }
    constexpr uint8_t alpha() const { return m_a; }

    constexpr float redFloat() const { return m_r / 255; }
    constexpr float greenFloat() const { return m_g / 255; }
    constexpr float blueFloat() const { return m_b / 255; }
    constexpr float alphaFloat() const { return m_a / 255; }

private:
    uint8_t m_r{}, m_g{}, m_b{}, m_a{};
};

inline const Color Color::BLACK{0, 0, 0, 255};

} // namespace Bjr

