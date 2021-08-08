#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Vec.hpp"


namespace Core
{
    struct Sphere
    {
        Vec position;
        double radius;
    };

    inline Sphere make_sphere(const Vec& position, double radius);
}

#include "SphereImp.hpp"

#endif // SPHERE_HPP
