#include "Math/Ray.hpp"

Ray::Ray(const Vector& position, const Vector& direction)
    : position(position), direction(direction)
{
}

Ray::Ray(const Core::Ray &ray)
    : position(ray.position), direction(ray.direction)
{
}

Ray::operator Core::Ray() const
{
    return Core::make_ray(position, direction);
}

bool Ray::intersectsSphere(double &t, const Vector &center, double radius) const
{
    auto sphere = Core::make_sphere(center, radius);
    return Core::ray_intersects(t, *this, sphere);
}
