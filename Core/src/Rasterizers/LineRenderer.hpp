#ifndef LINERENDERER_HPP
#define LINERENDERER_HPP

#include "StatusCodes.hpp"
#include "RenderTarget.hpp"


namespace Core
{
    StatusCode renderLine(RenderTarget& renderTarget, int x1, int y1, int x2, int y2, Pixel color);
}

#endif // LINERENDERER_HPP
