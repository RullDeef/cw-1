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

    inline int rect_area(const Rect& rect);

    inline bool is_valid(const Rect& rect);
    inline bool is_inside(const Rect& outer, const Rect& inner);
    inline bool is_inside(const Rect& rect, int x, int y);

    inline double get_x_aspect(const Rect& rect);
    inline double get_y_aspect(const Rect& rect);

    inline Rect get_inner_box(const Rect& rect);
    inline Rect get_outer_box(const Rect& rect);

    inline Vec map_point(const Rect& from_space, const Rect& to_space, const Vec& point);

    inline Vec inner_quad(const Rect& rect, int x, int y);
    inline Vec outer_quad(const Rect& rect, int x, int y);
}

#include "RectImp.hpp"

#endif // RECT_HPP
