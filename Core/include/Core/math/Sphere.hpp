#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Core/math/Vec.hpp"


namespace Core
{
    struct Sphere
    {
        Vec position;
        double radius;
    };

    inline Sphere make_sphere(const Vec& position, double radius);

    inline bool is_valid(const Sphere& sphere);
}

#include "Core/math/SphereImp.hpp"

#endif // SPHERE_HPP
