#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include <cstddef>
#include "Pixel.hpp"


namespace Core
{
    struct RenderTarget
    {
        Pixel* data;
        size_t width;
        size_t height;
    };

    bool isValid(const RenderTarget& renderTarget);

    Pixel getPixel(const RenderTarget& renderTarget, size_t row, size_t col);
    void setPixel(const RenderTarget& renderTarget, size_t row, size_t col, Pixel pixel);
}

#endif // RENDERTARGET_HPP
