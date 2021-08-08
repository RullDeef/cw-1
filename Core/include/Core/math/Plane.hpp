#ifndef PLANE_HPP
#define PLANE_HPP

#include "Vec.hpp"


namespace Core
{
    struct Plane
    {
        Vec position;
        Vec normal;
    };

    // inline Plane make_plane(double a, double b, double c, double d);
    inline Plane make_plane(const Vec& p1, const Vec& p2, const Vec& p3);
    inline Plane make_plane(const Vec& pos, const Vec& norm);

    inline void normalize(Plane& plane);

    inline double distance(const Plane& plane, const Vec& pos);

    inline Vec normal(const Plane& plane);
}

#include "PlaneImp.hpp"

#endif // PLANE_HPP
