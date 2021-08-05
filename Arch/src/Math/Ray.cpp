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
