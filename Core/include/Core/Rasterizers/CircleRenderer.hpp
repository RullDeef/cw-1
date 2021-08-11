#ifndef CIRCLERENDERER_HPP
#define CIRCLERENDERER_HPP

#include "Core/common/StatusCodes.hpp"
#include "Core/RenderTarget/RenderTarget.hpp"


namespace Core
{
    StatusCode renderCircle(RenderTarget& renderTarget, int circleX, int circleY, int radius, Pixel color);
}

#endif // CIRCLERENDERER_HPP
