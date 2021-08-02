#ifndef SPHEREIMP_HPP
#define SPHEREIMP_HPP

#include "Core/common/math/Sphere.hpp"


namespace Core
{
    inline Sphere make_sphere(const Vec& position, double radius)
    {
        Sphere sphere{};

        sphere.position = position;
        sphere.radius = radius;

        return sphere;
    }
}

#endif // SPHEREIMP_HPP
