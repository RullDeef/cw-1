#ifndef COLORIMP_HPP
#define COLORIMP_HPP

#include "Core/common/Color.hpp"


namespace Core
{
    constexpr Color make_color(double red, double green, double blue, double alpha) noexcept
    {
        Color color{};

        color.red = red;
        color.green = green;
        color.blue = blue;
        color.alpha = alpha;

        return color;
    }

    inline Pixel to_pixel(const Color& color)
    {
        Pixel pixel{};

        pixel.red = 255 * color.red;
        pixel.green = 255 * color.green;
        pixel.blue = 255 * color.blue;
        pixel.alpha = 255 * color.alpha;

        return pixel;
    }

    inline Color to_color(const Pixel& pixel)
    {
        Color res{};

        res.red = pixel.red / 255.0;
        res.green = pixel.green / 255.0;
        res.blue = pixel.blue / 255.0;
        res.alpha = pixel.alpha / 255.0;

        return res;
    }

    /// TODO: add blend modes (ADD, MULTIPLY, OVERLAY...)
    inline Color operator+(const Color& c1, const Color& c2)
    {
        Color res{};

        res.red = std::min(c1.red + c2.red, 1.0);
        res.green = std::min(c1.green + c2.green, 1.0);
        res.blue = std::min(c1.blue + c2.blue, 1.0);
        res.alpha = std::max(c1.alpha, c2.alpha);

        return res;
    }

    inline Color operator-(const Color &c1, const Color &c2)
    {
        Color res{};

        res.red = c1.red - c2.red;
        res.green = c1.green - c2.green;
        res.blue = c1.blue - c2.blue;
        res.alpha = c1.alpha;

        return res;
    }

    inline Color operator*(const Color& c1, const Color& c2)
    {
        Color res{};

        res.red = c1.red * c2.red;
        res.green = c1.green * c2.green;
        res.blue = c1.blue * c2.blue;
        res.alpha = std::max(c1.alpha, c2.alpha);

        return res;
    }

    inline Color operator*(const Color& col, double value)
    {
        Color res{};

        res.red = std::min(col.red * value, 1.0);
        res.green = std::min(col.green * value, 1.0);
        res.blue = std::min(col.blue * value, 1.0);
        res.alpha = col.alpha;

        return res;
    }

    inline Color operator/(const Color &col, double value)
    {
        return col * (1.0 / value);
    }

    inline Color operator*(double value, const Color& col)
    {
        return col * value;
    }

    inline Color& operator+=(Color& c1, const Color& c2)
    {
        c1 = c1 + c2;
        return c1;
    }
}

#endif // COLORIMP_HPP
