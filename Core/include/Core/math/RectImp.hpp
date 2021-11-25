#include "Rect.hpp"
#include <algorithm>


namespace Core
{
    template<typename T>
    inline Rect<T> make_rect(T width, T height, T left, T top)
    {
        Rect<T> rect;

        if (width <= 0 || height <= 0)
        {
            rect.width = 0;
            rect.height = 0;
            rect.left = 0;
            rect.top = 0;
        }
        else
        {
            rect.width = width;
            rect.height = height;
            rect.left = left;
            rect.top = top;
        }

        return rect;
    }

    inline RectF cast_rect(const RectI& rect)
    {
        return make_rect<float>(rect.width, rect.height, rect.left, rect.top);
    }

    inline RectI cast_rect(const RectF& rect)
    {
        return make_rect<int>(std::round(rect.width), std::round(rect.height), std::round(rect.left), std::round(rect.top));
    }

    template<typename T>
    inline T rect_area(const Rect<T>& rect)
    {
        return rect.width * rect.height;
    }

    template<typename T>
    inline bool is_valid(const Rect<T>& rect)
    {
        return rect.width > 0 && rect.height > 0; // && rect.left >= 0 && rect.top >= 0;
    }

    template<typename T>
    inline bool is_inside(const Rect<T>& outer, const Rect<T>& inner)
    {
        /// TODO: implement
        return true;
    }

    template<typename T>
    inline bool is_inside(const Rect<T>& rect, T x, T y);

    template<typename T>
    inline double get_x_aspect(const Rect<T>& rect)
    {
        if (rect.width < rect.height)
            return double(rect.height) / rect.width;
        return 1.0;
    }

    template<typename T>
    inline double get_y_aspect(const Rect<T>& rect)
    {
        if (rect.height < rect.width)
            return double(rect.width) / rect.height;
        return 1.0;
    }

    template<typename T>
    inline Rect<T> get_outer_box(const Rect<T>& rect)
    {
        if (rect.width < rect.height)
        {
            T left = rect.left - (rect.height - rect.width) / 2;
            return make_rect(rect.height, rect.height, left, rect.top);
        }
        else
        {
            T top = rect.top - (rect.width - rect.height) / 2;
            return make_rect(rect.width, rect.width, rect.left, top);
        }
    }

    template<typename T>
    inline Vec map_point(const Rect<T>& from_space, const Rect<T>& to_space, const Vec& point)
    {
        Vec res = point;

        double factor_w = double(to_space.width) / from_space.width;
        double factor_h = double(to_space.height) / from_space.height;

        res.x = to_space.left + (point.x - from_space.left) * factor_w;
        res.y = to_space.top + (point.y - from_space.top) * factor_h;

        return res;
    }

    template<typename T>
    inline Vec inner_quad(const Rect<T>& rect, T x, T y)
    {
        double vp = std::min(rect.width, rect.height);

        double vx = (2 * x - rect.width) / vp;
        double vy = (rect.height - 2 * y) / vp;

        return make_dir(vx, vy, 0);
    }

    template<typename T>
    inline Vec outer_quad(const Rect<T>& rect, T x, T y)
    {
        double vp = std::max(rect.width, rect.height);

        double vx = (2 * x - rect.width) / vp;
        double vy = (rect.height - 2 * y) / vp;

        return make_dir(vx, vy, 0);
    }
}
