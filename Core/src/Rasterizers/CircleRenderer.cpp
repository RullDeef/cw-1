#include "Core/Rasterizers/CircleRenderer.hpp"

using namespace Core;


StatusCode Core::renderCircle(RenderTarget& renderTarget, int x0, int y0, int radius, Pixel color)
{
    if (radius == 0.0)
        setPixel(renderTarget, y0, x0, color);
    else
    {
        int x = 0;
        int y = radius;
        int d = 2 * (1 - radius);

        setPixel(renderTarget, y0 + radius, x0, color);
        setPixel(renderTarget, y0 - radius, x0, color);
        setPixel(renderTarget, y0, x0 + radius, color);
        setPixel(renderTarget, y0, x0 - radius, color);

        while (y >= x)
        {
            if (d < 0)
            {
                if (2 * (d + y) - 1 < 0) // horizontal move
                {
                    x++;
                    d += 2 * x + 1;
                }
                else // diagonal move
                {
                    x++;
                    y--;
                    d += 2 * (x - y + 1);
                }
            }
            else if (d > 0)
            {
                if (2 * (d - x) - 1 < 0) // diagonal move
                {
                    x++;
                    y--;
                    d += 2 * (x - y + 1);
                }
                else // vertical move
                {
                    y--;
                    d += -2 * y + 1;
                }
            }
            else // diagonal move
            {
                x++;
                y--;
                d += 2 * (x - y + 1);
            }

            setPixel(renderTarget, y0 + y, x0 + x, color);
            setPixel(renderTarget, y0 + y, x0 - x, color);
            setPixel(renderTarget, y0 - y, x0 - x, color);
            setPixel(renderTarget, y0 - y, x0 + x, color);
            setPixel(renderTarget, y0 + x, x0 + y, color);
            setPixel(renderTarget, y0 + x, x0 - y, color);
            setPixel(renderTarget, y0 - x, x0 - y, color);
            setPixel(renderTarget, y0 - x, x0 + y, color);
        }
    }

    return StatusCode::Success;
}

StatusCode Core::renderCircle(RenderTarget& renderTarget, int circleX, int circleY, int radius, Color color)
{
    return renderCircle(renderTarget, circleX, circleY, radius, to_pixel(color));
}
