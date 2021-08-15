#include "Math/Ray.hpp"

Ray::Ray(const Vector& position, const Vector& direction, const Camera* camera, Rect viewport)
    : position(position), direction(direction), camera(camera), viewport(viewport)
{
}

Ray::Ray(const Core::Ray &ray)
    : position(ray.position), direction(ray.direction), camera(nullptr), viewport(0, 0, 0, 0)
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

bool Ray::intersectsPlane(double& t, const Vector& pos, const Vector& normal) const
{
    auto plane = Core::make_plane(pos, normal);
    return Core::ray_intersects(t, *this, plane);
}
