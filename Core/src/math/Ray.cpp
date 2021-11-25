#include "Core/math/Ray.hpp"
#include "Core/Scene/Scene.hpp"

using namespace Core;


Ray Core::make_ray(const Vec &position, const Vec &direction)
{
    Ray ray{};

    if (is_zero(direction))
    {
        ray.position = make_pos();
        ray.direction = make_dir();
    }
    else
    {
        ray.position = position;
        ray.direction = direction;
    }

    return ray;
}

bool Core::is_valid(const Ray& ray)
{
    return is_normal(ray.direction);
}

Vec Core::ray_at(const Ray &ray, double t)
{
    return ray.position + t * ray.direction;
}

void Core::advance(Ray& ray, double distance)
{
    ray.position += ray.direction * distance;
}

Ray Core::ray_reflection(const Ray& src, const Face& face)
{
    Vec n = get_mean_normal(face); // TODO: make face normal interpolation
    Vec new_dir = src.direction - 2 * dot(n, src.direction) * n;
    return make_ray(src.position, new_dir);
}

Ray Core::ray_refraction(const Ray& src, const Face& face, double IOR)
{
    Vec n = get_mean_normal(face); // TODO: same as above
    Vec tan = normalized(src.direction - dot(n, src.direction) * n);

    // double r_x = dot(tan, src.direction);
    double r_y = dot(n, src.direction);

    double rp_y = r_y / IOR;
    double rp_x = std::sqrt(1.0 - rp_y * rp_y);

    Vec new_dir = rp_x * tan + rp_y * n;
    return make_ray(src.position, new_dir);
}

bool Core::ray_intersects(double& t, const Ray& ray, const Sphere& sphere)
{
    Vec h = sphere.position - ray.position;

    double dh = dot(ray.direction, h);
    double D_4 = dh * dh - dot(h, h) + sphere.radius * sphere.radius;

    if (D_4 < 0.0)
        return false;

    t = dh - std::sqrt(D_4);
    if (t < 0.0)
        t = dh + std::sqrt(D_4);

    return t > 0.0;
}

bool Core::ray_intersects(double& t, const Ray& ray, const Plane& plane)
{
    double wn = dot(plane.position - ray.position, plane.normal);
    double dn = dot(ray.direction, plane.normal);

    t = wn / dn;
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

bool Core::ray_intersects(double& t, const Ray& ray, const Mesh& mesh)
{
    Sphere sphere = get_bounding_sphere(const_cast<Mesh&>(mesh));
    if (!ray_intersects(t, ray, sphere))
        return false;

    double tMin = std::numeric_limits<double>::infinity();
    bool intersects = false;

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        Face face{};
        if (get(mesh.faces, i, face))
        {
            face = mesh.model_mat * face;
            if (ray_intersects(t, ray, face))
            {
                intersects = true;
                tMin = std::min(tMin, t);
            }
        }
    }

    t = tMin;
    return intersects;
}

bool Core::ray_intersects(double& t, const Ray& ray, Mesh& mesh, const Scene& scene)
{
    double tMin = std::numeric_limits<double>::infinity();
    bool intersects = false;

    for (auto node = scene.meshList.head; node; node = node->next)
    {
        if (ray_intersects(t, ray, node->value))
        {
            if (t < tMin)
            {
                tMin = t;
                mesh = node->value;
            }
        }
    }

    t = tMin;
    return intersects;
}
