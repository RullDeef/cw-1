#include "Rect.hpp"
#include <algorithm>


namespace Core
{
    inline Rect make_rect(int width, int height, int left, int top)
    {
        Rect rect;

        rect.width = width;
        rect.height = height;
        rect.left = left;
        rect.top = top;

        return rect;
    }

    inline int rect_area(const Rect& rect)
    {
        return rect.width * rect.height;
    }

    inline bool is_valid(const Rect &rect)
    {
        return rect.left >= 0 && rect.top >= 0
            && rect.width > 0 && rect.height > 0;
    }

    inline bool is_inside(const Rect &outer, const Rect &inner)
    {
        /// TODO: implement
        return true;
    }

    inline bool is_inside(const Rect &rect, int x, int y);

    inline double get_x_aspect(const Rect& rect)
    {
        if (rect.width < rect.height)
            return double(rect.height) / rect.width;
        return 1.0;
    }

    inline double get_y_aspect(const Rect& rect)
    {
        if (rect.height < rect.width)
            return double(rect.width) / rect.height;
        return 1.0;
    }

    inline Rect get_outer_box(const Rect& rect)
    {
        if (rect.width < rect.height)
        {
            int left = rect.left - (rect.height - rect.width) / 2;
            return make_rect(rect.height, rect.height, left, rect.top);
        }
        else
        {
            int top = rect.top - (rect.width - rect.height) / 2;
            return make_rect(rect.width, rect.width, rect.left, top);
        }
    }

    inline Vec map_point(const Rect& from_space, const Rect& to_space, const Vec& point)
    {
        Vec res = point;

        double factor_w = double(to_space.width) / from_space.width;
        double factor_h = double(to_space.height) / from_space.height;

        res.x = to_space.left + (point.x - from_space.left) * factor_w;
        res.y = to_space.top + (point.y - from_space.top) * factor_h;

        return res;
    }

    inline Vec inner_quad(const Rect& rect, int x, int y)
    {
        double vp = std::min(rect.width, rect.height);

        double vx = (2 * x - rect.width) / vp;
        double vy = (rect.height - 2 * y) / vp;

        return make_dir(vx, vy);
    }

    inline Vec outer_quad(const Rect& rect, int x, int y)
    {
        double vp = std::max(rect.width, rect.height);

        double vx = (2 * x - rect.width) / vp;
        double vy = (rect.height - 2 * y) / vp;

        return make_dir(vx, vy);
    }
}
