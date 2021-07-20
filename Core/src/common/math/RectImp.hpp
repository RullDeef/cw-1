#include "Rect.hpp"


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

inline bool is_valid(const Rect &rect)
{
    return rect.left >= 0 && rect.top >= 0
        && rect.width > 0 && rect.height > 0;
}

inline bool is_inside(const Rect &outer, const Rect &inner);
inline bool is_inside(const Rect &rect, int x, int y);

}
