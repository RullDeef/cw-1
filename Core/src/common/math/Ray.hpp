#ifndef RAY_HPP
#define RAY_HPP

#include "Vec.hpp"


namespace Core
{
    struct Ray
    {
        Vec position;
        Vec direction;
    };

    constexpr Ray make_ray(const Vec& position, const Vec& direction);

    bool ray_intersects();
}

#endif // RAY_HPP
