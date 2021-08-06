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
