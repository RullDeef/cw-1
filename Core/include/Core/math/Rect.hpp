#ifndef RECT_HPP
#define RECT_HPP

#include "Vec.hpp"


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

    inline Rect get_inner_box(const Rect& rect);
    inline Rect get_outer_box(const Rect& rect);

    inline Vec map_point(const Rect& from_space, const Rect& to_space, const Vec& point);
}

#include "RectImp.hpp"

#endif // RECT_HPP
