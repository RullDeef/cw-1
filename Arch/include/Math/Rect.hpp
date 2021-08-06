#ifndef ARCH_RECT_HPP
#define ARCH_RECT_HPP

#include "Core/common/math/Rect.hpp"

class Rect
{
public:
    Rect(int top, int left, int width, int height);
    Rect(const Core::Rect& rect);

    operator Core::Rect() const;

private:
    int top;
    int left;
    int width;
    int height;
};

#endif //ARCH_RECT_HPP
