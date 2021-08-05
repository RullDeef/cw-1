#include "Core/RenderTarget/RenderTarget.hpp"

using namespace Core;


void Core::setPixel(const RenderTarget& renderTarget, size_t row, size_t col, Pixel pixel)
{
    if (row >= renderTarget.height || col >= renderTarget.width)
    {
        // log error
        return;
    }

    renderTarget.data[row * renderTarget.width + col] = pixel;
}

RenderTarget Core::make_render_target(unsigned char *data, size_t w, size_t h)
{
    RenderTarget res{};

    res.data = (Core::Pixel*)data;
    res.width = w;
    res.height = h;

    return res;
}
