#include "Core/common/math/Ray.hpp"

using namespace Core;


Ray Core::make_ray(const Vec &position, const Vec &direction)
{
    Ray ray{};

    ray.position = position;
    ray.direction = direction;

    return ray;
}

Vec Core::ray_at(const Ray &ray, double t)
{
    return ray.position + t * ray.direction;
}

bool Core::ray_intersects(double& t, const Ray& ray, const Plane& plane)
{
    double dot_pos = ray.position.x * plane.a + ray.position.y * plane.b + ray.position.z * plane.c + plane.d;
    double dot_dir = ray.direction.x * plane.a + ray.direction.y * plane.b + ray.direction.z * plane.c;

    t = - dot_pos / dot_dir;

    return t > 0;
}

bool Core::ray_intersects(double& t, const Ray& ray, const Face& face)
{
    Plane plane = make_plane(face.verts[0].position, face.verts[1].position, face.verts[2].position);
    if (ray_intersects(t, ray, plane))
    {
        Vec v1 = face.verts[1].position - face.verts[0].position;
        Vec v2 = face.verts[2].position - face.verts[1].position;
        Vec v3 = face.verts[0].position - face.verts[2].position;

        Vec norm = cross(v1, v2);
        Vec pos = ray_at(ray, t);

        Vec x1 = cross(v1, pos - face.verts[0].position);
        Vec x2 = cross(v2, pos - face.verts[1].position);
        Vec x3 = cross(v3, pos - face.verts[2].position);

        bool d1 = dot(norm, x1) >= 0;
        bool d2 = dot(norm, x2) >= 0;
        bool d3 = dot(norm, x3) >= 0;

        return d1 && d2 && d3;
    }
    return false;
}
