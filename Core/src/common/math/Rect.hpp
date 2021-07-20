#ifndef RECT_HPP
#define RECT_HPP


namespace Core
{
    struct Rect
    {
        int top;
        int left;
        int width;
        int height;
    };

    inline Rect make_rect(int width, int height, int left = 0, int top = 0);

    inline bool is_valid(const Rect& rect);
    inline bool is_inside(const Rect& outer, const Rect& inner);
    inline bool is_inside(const Rect& rect, int x, int y);
}

#include "RectImp.hpp"

#endif // RECT_HPP
