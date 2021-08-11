#ifndef ARCH_COLOR_HPP
#define ARCH_COLOR_HPP

#include <Core/common/Color.hpp>
#include "Math/Vector.hpp"


class Color
{
public:
    constexpr explicit Color(double red = 0.0, double green = 0.0, double blue = 0.0, double alpha = 1.0) noexcept
        : mRed(red), mGreen(green), mBlue(blue), mAlpha(alpha) {}
    Color(const Vector& v) noexcept
        : mRed(v.getX()), mGreen(v.getY()), mBlue(v.getZ()), mAlpha(v.getW()) {}
    constexpr Color(const Core::Color& col) noexcept
        : mRed(col.red), mGreen(col.green), mBlue(col.blue), mAlpha(col.alpha) {}

    inline operator Vector() const { return Vector(mRed, mGreen, mBlue, mAlpha); }
    inline operator Core::Color() const { return Core::make_color(mRed, mGreen, mBlue, mAlpha); }
    inline operator Core::Pixel() const { return Core::to_pixel(*this); }

    inline double getRed() const noexcept { return mRed; }
    inline double getGreen() const noexcept { return mGreen; }
    inline double getBlue() const noexcept { return mBlue; }
    inline double getAlpha() const noexcept { return mAlpha; }

    inline int getRedByte() const noexcept { return 255 * mRed; }
    inline int getGreenByte() const noexcept { return 255 * mGreen; }
    inline int getBlueByte() const noexcept { return 255 * mBlue; }
    inline int getAlphaByte() const noexcept { return 255 * mAlpha; }

    constexpr static Color transparent() noexcept { return Color(0.0, 0.0, 0.0, 0.0); }
    constexpr static Color black() noexcept { return Color(0.0, 0.0, 0.0, 1.0); }
    constexpr static Color white() noexcept { return Color(1.0, 1.0, 1.0, 1.0); }
    constexpr static Color green() noexcept { return Color(0.0, 1.0, 0.0, 1.0); }

private:
    double mRed;
    double mGreen;
    double mBlue;
    double mAlpha;
};

#endif // ARCH_COLOR_HPP
