#ifndef COLOR_HPP
#define COLOR_HPP

#include "Core/math/Vec.hpp"
#include "Core/common/Pixel.hpp"


namespace Core
{
    struct Color
    {
        double red;
        double green;
        double blue;
        double alpha;
    };

    constexpr Color make_color(double red = 0.0, double green = 0.0, double blue = 0.0, double alpha = 1.0) noexcept;

    inline Pixel to_pixel(const Color& color);
    inline Color to_color(const Pixel& pixel);

    inline Color operator+(const Color& c1, const Color& c2);
    inline Color operator-(const Color& c1, const Color& c2);
    inline Color operator*(const Color& c1, const Color& c2);
    inline Color operator*(const Color& col, double value);
    inline Color operator/(const Color& col, double value);
    inline Color operator*(double value, const Color& col);

    inline Color& operator+=(Color& c1, const Color& c2);

    namespace Colors
    {
        const Color black { 0.0, 0.0, 0.0, 1.0 };
        const Color white { 1.0, 1.0, 1.0, 1.0 };

        const Color orange { 1.0, 0.5, 0.0, 1.0 };
    }
}

#include "Core/common/ColorImp.hpp"

#endif // COLOR_HPP
