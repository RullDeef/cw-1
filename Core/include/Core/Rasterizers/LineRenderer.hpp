#ifndef LINERENDERER_HPP
#define LINERENDERER_HPP

#include "Core/common/StatusCodes.hpp"
#include "Core/RenderTarget/RenderTarget.hpp"


namespace Core
{
    StatusCode renderLine(RenderTarget& renderTarget, int x1, int y1, int x2, int y2, Pixel color);
}

#endif // LINERENDERER_HPP
