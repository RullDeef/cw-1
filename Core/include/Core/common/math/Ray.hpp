#ifndef RAY_HPP
#define RAY_HPP

#include "Core/common/math/Vec.hpp"
#include "Core/common/math/Plane.hpp"
#include "Core/common/math/Sphere.hpp"
#include "Core/Objects/Mesh.hpp"


namespace Core
{
    struct Ray
    {
        Vec position;
        Vec direction;
    };

    Ray make_ray(const Vec& position, const Vec& direction);

    Vec ray_at(const Ray& ray, double t);

    bool ray_intersects(double& t, const Ray& ray, const Sphere& sphere);
    bool ray_intersects(double& t, const Ray& ray, const Plane& plane);
    bool ray_intersects(double& t, const Ray& ray, const Face& face);
}

#endif // RAY_HPP
