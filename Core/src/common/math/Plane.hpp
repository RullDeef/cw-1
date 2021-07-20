#ifndef PLANE_HPP
#define PLANE_HPP

#include "Vec.hpp"


namespace Core
{
    struct Plane
    {
        double a;
        double b;
        double c;
        double d;
    };

    constexpr Plane make_plane(double a, double b, double c, double d);
    constexpr Plane make_plane(const Vec& p1, const Vec& p2, const Vec& p3);
    constexpr Plane make_plane(const Vec& pos, const Vec& norm);

    inline double distance(const Plane& plane, const Vec& pos);
}

#endif // PLANE_HPP
