#include "RenderTarget.hpp"

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
