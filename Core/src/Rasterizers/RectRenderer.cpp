#include <algorithm>
#include "Core/Rasterizers/RectRenderer.hpp"

using namespace Core;


StatusCode Core::renderRect(RenderTarget &renderTarget, const Core::RectI &rect, Pixel color)
{
    if (!is_valid(rect))
        return StatusCode::InvalidRect;

    return renderRect(renderTarget, rect.left, rect.top, rect.left + rect.width, rect.top + rect.height, color);
}

StatusCode Core::renderRect(RenderTarget &renderTarget, int x1, int y1, int x2, int y2, Pixel color)
{
    if (!is_valid(renderTarget))
        return StatusCode::InvalidRenderTarget;

    if (x2 < x1) std::swap(x1, x2);
    if (y2 < y1) std::swap(y1, y2);

    for (int x = x1; x < x2; x++)
    {
        setPixel(renderTarget, x, y1, color);
        setPixel(renderTarget, x, y2, color);
    }

    for (int y = y1; y < y2; y++)
    {
        setPixel(renderTarget, x1, y, color);
        setPixel(renderTarget, x2, y, color);
    }

    return StatusCode::Success;
}
