#ifndef RECT_HPP
#define RECT_HPP

#include "Core/math/Vec.hpp"


namespace Core
{
    template<typename T>
    struct Rect
    {
        T top;
        T left;
        T width;
        T height;
    };

    using RectI = Rect<int>;
    using RectF = Rect<float>;

    template<typename T>
    inline Rect<T> make_rect(T width, T height, T left = 0, T top = 0);

    inline RectF cast_rect(const RectI& rect);
    inline RectI cast_rect(const RectF& rect);

    template<typename T>
    inline T rect_area(const Rect<T>& rect);

    template<typename T>
    inline bool is_valid(const Rect<T>& rect);

    template<typename T>
    inline bool is_inside(const Rect<T>& outer, const Rect<T>& inner);

    template<typename T>
    inline bool is_inside(const Rect<T>& rect, T x, T y);

    template<typename T>
    inline double get_x_aspect(const Rect<T>& rect);

    template<typename T>
    inline double get_y_aspect(const Rect<T>& rect);

    template<typename T>
    inline Rect<T> get_inner_box(const Rect<T>& rect);

    template<typename T>
    inline Rect<T> get_outer_box(const Rect<T>& rect);

    template<typename T>
    inline Vec map_point(const Rect<T>& from_space, const Rect<T>& to_space, const Vec& point);

    template<typename T>
    inline Vec inner_quad(const Rect<T>& rect, T x, T y);

    template<typename T>
    inline Vec outer_quad(const Rect<T>& rect, T x, T y);
}

#include "Core/math/RectImp.hpp"

#endif // RECT_HPP
