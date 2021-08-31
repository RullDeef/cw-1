#ifndef RAY_HPP
#define RAY_HPP

#include "Vec.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Core/Objects/Face.hpp"
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
    void advance(Ray& ray, double distance);

    Ray ray_reflection(const Ray& src, const Face& face);
    Ray ray_refraction(const Ray& src, const Face& face, double IOR);

    bool ray_intersects(double& t, const Ray& ray, const Sphere& sphere);
    bool ray_intersects(double& t, const Ray& ray, const Plane& plane);
    bool ray_intersects(double& t, const Ray& ray, const Face& face);
    bool ray_intersects(double& t, const Ray& ray, const Mesh& mesh);
}

#endif // RAY_HPP
