#ifndef ARCH_RECT_HPP
#define ARCH_RECT_HPP

#include "Core/math/Rect.hpp"
#include "Math/Vector.hpp"


class Rect
{
public:
    Rect(int top, int left, int width, int height);
    Rect(const Core::Rect& rect);

    operator Core::Rect() const;

    Vector innerQuad(int x, int y) const;
    Vector outerQuad(int x, int y) const;

private:
    int top;
    int left;
    int width;
    int height;
};

#endif //ARCH_RECT_HPP
