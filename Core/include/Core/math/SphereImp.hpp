#ifndef SPHEREIMP_HPP
#define SPHEREIMP_HPP

#include "Core/math/Sphere.hpp"


namespace Core
{
    inline Sphere make_sphere(const Vec& position, double radius)
    {
        Sphere sphere{};

        sphere.position = position;
        sphere.radius = radius;

        return sphere;
    }

    inline bool is_valid(const Sphere& sphere)
    {
        return sphere.radius > 0.0;
    }
}

#endif // SPHEREIMP_HPP
