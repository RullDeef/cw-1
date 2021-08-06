#include "Math/Rect.hpp"

Rect::Rect(int top, int left, int width, int height)
    : top(top), left(left), width(width), height(height)
{
}

Rect::Rect(const Core::Rect &rect)
    : top(rect.top), left(rect.left), width(rect.width), height(rect.height)
{
}

Rect::operator Core::Rect() const
{
    return Core::make_rect(width, height, left, top);
}

Vector Rect::innerQuad(int x, int y) const
{
    double vp = std::min(width, height);

    double vx = (2 * x - width) / vp;
    double vy = (height - 2 * y) / vp;

    return Vector(vx, vy, 0.0, 0.0);
}

Vector Rect::outerQuad(int x, int y) const
{
    double vp = std::max(width, height);

    double vx = (2 * x - width) / vp;
    double vy = (height - 2 * y) / vp;

    return Vector(vx, vy, 0.0, 0.0);
}
