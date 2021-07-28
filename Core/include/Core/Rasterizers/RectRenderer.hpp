#ifndef RECTRENDERER_HPP
#define RECTRENDERER_HPP

#include "Core/common/StatusCodes.hpp"
#include "Core/common/math/Rect.hpp"
#include "Core/RenderTarget/RenderTarget.hpp"


namespace Core
{
    StatusCode renderRect(RenderTarget &renderTarget, const Core::Rect &rect, Pixel color);

    StatusCode renderRect(RenderTarget &renderTarget, int x1, int y1, int x2, int y2, Pixel color);
}

#endif // RECTRENDERER_HPP
