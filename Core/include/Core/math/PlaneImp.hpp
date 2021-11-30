#ifndef PLANEIMP_HPP
#define PLANEIMP_HPP

#include "Plane.hpp"

namespace Core
{
//    inline Plane make_plane(double a, double b, double c, double d)
//    {
//        Plane plane{};
//
//        plane.a = a;
//        plane.b = b;
//        plane.c = c;
//        plane.d = d;
//
//        return plane;
//    }

    inline Plane make_plane(const Vec& p1, const Vec& p2, const Vec& p3)
    {
        Vec norm = cross(p2 - p1, p3 - p1);
        return make_plane(p1, norm);
    }

    inline Plane make_plane(const Vec& pos, const Vec& norm)
    {
        Plane plane{};

        if (is_zero(norm))
        {
            plane.position = make_pos(0, 0, 0);
            plane.normal = make_dir(0, 0, 0);
        }
        else
        {
            plane.position = pos;
            plane.normal = normalized(norm);
        }

        return plane;
    }

    inline bool is_valid(const Plane& plane)
    {
        return is_normal(plane.normal);
    }

//    inline double distance(const Plane& plane, const Vec& pos)
//    {
//        return -1;
//    }

//    inline Vec normal(const Plane& plane)
//    {
//        return normalized(make_dir(plane.a, plane.b, plane.c));
//    }
}

#endif // PLANEIMP_HPP
