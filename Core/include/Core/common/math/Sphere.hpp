#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Core/common/math/Vec.hpp"


namespace Core
{
    struct Sphere
    {
        Vec position;
        double radius;
    };

    inline Sphere make_sphere(const Vec& position, double radius);
}

#include "Core/common/math/SphereImp.hpp"

#endif // SPHERE_HPP
