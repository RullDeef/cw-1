#include <cmath>
#include "LineRenderer.hpp"

using namespace Core;


StatusCode Core::renderLine(RenderTarget& renderTarget, int x1, int y1, int x2, int y2, Pixel color)
{
    // используется алгоритм Брезенхема
    int deltaX = std::abs(x2 - x1);
    int deltaY = std::abs(y2 - y1);

    int error;
    int deltaError;

    if (deltaX == 0 && deltaY == 0)
    {
        setPixel(renderTarget, y1, x1, color);
        //image.setPixel(x1, y1, color);
    }
    else if (deltaX <= deltaY)
    {
        int x = x1;

        deltaError = deltaX;
        error = deltaError;

        if (y1 <= y2)
        {
            if (x1 <= x2)
            {
                for (int y = y1; y <= y2; y++)
                {
                    setPixel(renderTarget, y, x, color);
                    //image.setPixel(x, y, color);

                    error += deltaError;
                    if (error >= deltaY)
                    {
                        error -= deltaY;
                        x++;
                    }
                }
            }
            else
            {
                for (int y = y1; y <= y2; y++)
                {
                    setPixel(renderTarget, y, x, color);
                    //image.setPixel(x, y, color);

                    error += deltaError;
                    if (error >= deltaY)
                    {
                        error -= deltaY;
                        x--;
                    }
                }
            }
        }
        else
        {
            if (x1 <= x2)
            {
                for (int y = y1; y >= y2; y--)
                {
                    setPixel(renderTarget, y, x, color);
                    //image.setPixel(x, y, color);

                    error += deltaError;
                    if (error >= deltaY)
                    {
                        error -= deltaY;
                        x++;
                    }
                }
            }
            else
            {
                for (int y = y1; y >= y2; y--)
                {
                    setPixel(renderTarget, y, x, color);
                    //image.setPixel(x, y, color);

                    error += deltaError;
                    if (error >= deltaY)
                    {
                        error -= deltaY;
                        x--;
                    }
                }
            }
        }
    }
    else
    {
        int y = y1;

        deltaError = deltaY;
        error = deltaError;

        if (x1 <= x2)
        {
            if (y1 <= y2)
            {
                for (int x = x1; x <= x2; x++)
                {
                    setPixel(renderTarget, y, x, color);
                    //image.setPixel(x, y, color);

                    error += deltaError;
                    if (error >= deltaX)
                    {
                        error -= deltaX;
                        y++;
                    }
                }
            }
            else
            {
                for (int x = x1; x <= x2; x++)
                {
                    setPixel(renderTarget, y, x, color);
                    //image.setPixel(x, y, color);

                    error += deltaError;
                    if (error > deltaX)
                    {
                        error -= deltaX;
                        y--;
                    }
                }
            }
        }
        else
        {
            if (y1 <= y2)
            {
                for (int x = x1; x >= x2; x--)
                {
                    setPixel(renderTarget, y, x, color);
                    //image.setPixel(x, y, color);

                    error += deltaError;
                    if (error >= deltaX)
                    {
                        error -= deltaX;
                        y++;
                    }
                }
            }
            else
            {
                for (int x = x1; x >= x2; x--)
                {
                    setPixel(renderTarget, y, x, color);
                    //image.setPixel(x, y, color);

                    error += deltaError;
                    if (error >= deltaX)
                    {
                        error -= deltaX;
                        y--;
                    }
                }
            }
        }
    }

    return StatusCode::Success;
}