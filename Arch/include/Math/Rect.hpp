#ifndef ARCH_RECT_HPP
#define ARCH_RECT_HPP

#include "Core/math/Rect.hpp"
#include "Math/Vector.hpp"


class Rect
{
public:
    Rect(int top, int left, int width, int height);
    Rect(const Core::RectF& rect);
    Rect(const Core::RectI& rect);

    operator Core::RectI() const;
    operator Core::RectF() const;

    [[nodiscard]] Vector innerQuad(float x, float y) const;
    [[nodiscard]] Vector outerQuad(float x, float y) const;

    [[nodiscard]] Vector fitIn(const Vector& point) const;

private:
    [[nodiscard]] bool isValid() const;

    float top;
    float left;
    float width;
    float height;
};

#endif //ARCH_RECT_HPP
