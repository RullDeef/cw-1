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

    /**
     * Finds mix of two colors
     *
     * @param c1 - first color
     * @param c2 - second color
     * @param t - must be in range 0-1, where 0 returns c1 and 0 returns c2
     * @returns mixed color
     */
    inline Color mix(const Color& c1, const Color& c2, double t);

    /**
     * Finds soft mix of two colors. Function used in calculation is error function.
     *
     * @param c1 - first color
     * @param c2 - second color
     * @param t - can be any finite number, where lower returns c1 and higher returns c2
     * @returns mixed color
     */
    inline Color soft_mix(const Color& c1, const Color& c2, double t);

    inline Color operator+(const Color& c1, const Color& c2);
    inline Color operator-(const Color& c1, const Color& c2);
    inline Color operator*(const Color& c1, const Color& c2);
    inline Color operator*(const Color& col, double value);
    inline Color operator/(const Color& col, double value);
    inline Color operator*(double value, const Color& col);

    inline Color& operator+=(Color& c1, const Color& c2);

    namespace Colors
    {
        const Color transparent { 0.0, 0.0, 0.0, 0.0 };

        const Color black { 0.0, 0.0, 0.0, 1.0 };
        const Color white { 1.0, 1.0, 1.0, 1.0 };

        const Color green { 0.0, 1.0, 0.0, 1.0 };

        const Color cyan { 0.0, 1.0, 1.0, 1.0 };

        const Color light_cyan { 0.47, 0.87, 0.78, 1.0 };

        const Color orange { 1.0, 0.5, 0.0, 1.0 };
    }
}

#include "Core/common/ColorImp.hpp"

#endif // COLOR_HPP
