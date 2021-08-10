#ifndef ARCH_COLOR_HPP
#define ARCH_COLOR_HPP

#include <Core/common/Color.hpp>
#include "Math/Vector.hpp"


class Color
{
public:
    constexpr explicit Color(double red = 0.0, double green = 0.0, double blue = 0.0, double alpha = 1.0) noexcept
        : red(red), green(green), blue(blue), alpha(alpha) {}
    Color(const Vector& v) noexcept
        : red(v.getX()), green(v.getY()), blue(v.getZ()), alpha(v.getW()) {}
    constexpr Color(const Core::Color& col) noexcept
        : red(col.red), green(col.green), blue(col.blue), alpha(col.alpha) {}

    inline operator Vector() const { return Vector(red, green, blue, alpha); }
    inline operator Core::Color() const { return Core::make_color(red, green, blue, alpha); }
    inline operator Core::Pixel() const { return Core::to_pixel(*this); }

    constexpr static Color transparent() noexcept { return Color(0.0, 0.0, 0.0, 0.0); }
    constexpr static Color black() noexcept { return Color(0.0, 0.0, 0.0, 1.0); }
    constexpr static Color white() noexcept { return Color(1.0, 1.0, 1.0, 1.0); }

private:
    double red;
    double green;
    double blue;
    double alpha;
};

#endif // ARCH_COLOR_HPP
