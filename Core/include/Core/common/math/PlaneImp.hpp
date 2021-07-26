#ifndef PLANEIMP_HPP
#define PLANEIMP_HPP

#include "Plane.hpp"

namespace Core
{
    inline Plane make_plane(double a, double b, double c, double d)
    {
        Plane plane{};

        plane.a = a;
        plane.b = b;
        plane.c = c;
        plane.d = d;

        return plane;
    }

    inline Plane make_plane(const Vec& p1, const Vec& p2, const Vec& p3)
    {
        Vec norm = cross(p2 - p1, p3 - p1);

        Plane plane{};

        plane.a = norm.x;
        plane.b = norm.y;
        plane.c = norm.z;
        plane.d = -dot(norm, p1);

        normalize(plane);
        return plane;
    }

    inline Plane make_plane(const Vec& pos, const Vec& norm);

    inline void normalize(Plane& plane)
    {
        double d = plane.a * plane.a + plane.b * plane.b + plane.c * plane.c;

        if (std::abs(d - 1.0) > 0.00001)
        {
            plane.a /= d;
            plane.b /= d;
            plane.c /= d;
            plane.d /= d;
        }
    }

    inline double distance(const Plane& plane, const Vec& pos)
    {
        return -1;
    }

    inline Vec normal(const Plane& plane)
    {
        return make_dir(plane.a, plane.b, plane.c);
    }
}

#endif // PLANEIMP_HPP
