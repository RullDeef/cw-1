#include "Core/RenderTarget/RenderTarget.hpp"

using namespace Core;


RenderTarget Core::make_render_target(unsigned char *data, size_t w, size_t h)
{
    RenderTarget res{};

    res.data = (Core::Pixel*)data;
    res.width = w;
    res.height = h;

    return res;
}

Rect Core::get_viewport(const RenderTarget& renderTarget)
{
    return make_rect(renderTarget.width, renderTarget.height);
}

void Core::setPixel(RenderTarget& renderTarget, size_t row, size_t col, Pixel pixel)
{
    if (row >= renderTarget.height || col >= renderTarget.width)
        return; /// TODO: log error

    renderTarget.data[row * renderTarget.width + col] = pixel;
}

void Core::fill(RenderTarget& renderTarget, Pixel pixel)
{
    for (size_t row = 0; row < renderTarget.height; row++)
        for (size_t col = 0; col < renderTarget.width; col++)
            setPixel(renderTarget, row, col, pixel);
}