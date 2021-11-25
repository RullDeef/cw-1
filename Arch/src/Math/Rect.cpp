#include <stdexcept>
#include "Math/Rect.hpp"


Rect::Rect(int top, int left, int width, int height)
    : top(top), left(left), width(width), height(height)
{
    if (!isValid())
        throw std::runtime_error("bad Rect() args.");
}

Rect::Rect(const Core::RectI &rect)
    : top(rect.top), left(rect.left), width(rect.width), height(rect.height)
{
    if (!isValid())
        throw std::runtime_error("bad Rect() args.");
}

Rect::Rect(const Core::RectF &rect)
        : top(rect.top), left(rect.left), width(rect.width), height(rect.height)
{
    if (!isValid())
        throw std::runtime_error("bad Rect() args.");
}

Rect::operator Core::RectI() const
{
    Core::RectF rect = *this;
    return Core::cast_rect(rect);
}

Rect::operator Core::RectF() const
{
    return Core::make_rect(width, height, left, top);
}

Vector Rect::innerQuad(float x, float y) const
{
    double vp = std::min(width, height);

    double vx = (2 * x - width) / vp;
    double vy = (height - 2 * y) / vp;

    return Vector(vx, vy, 0.0, 0.0);
}

Vector Rect::outerQuad(float x, float y) const
{
    double vp = std::max(width, height);

    double vx = (2 * x - width) / vp;
    double vy = (height - 2 * y) / vp;

    return Vector(vx, vy, 0.0, 0.0);
}

Vector Rect::fitIn(const Vector& point) const
{
    double vmax2 = std::max<double>(width, height) / 2;
    double x = left + point.getX() * vmax2 + double(width) / 2;
    double y = top - point.getY() * vmax2 + double(height) / 2;

    return Vector(x, y, point.getZ(), point.getW());
}

bool Rect::isValid() const
{
    Core::RectF rect = *this;
    return Core::is_valid(rect);
}