#include <exception>
#include <iostream>
#include "Core/Objects/Camera.hpp"
#include "Core/math/Ray.hpp"

using namespace Core;

constexpr auto PI = 3.1415926535;
constexpr auto PI_2 = PI / 2;


void test_mat_mult()
{
    Mat left = { 9, 2, 12, 3,
                 4, 3, 2, 8,
                 10, 8, 2, 4,
                 7, 1, 3, 4 };
    Mat right = { 2, 1, 4, 5,
                  4, 8, 9, 2,
                  4, 7, 5, 3,
                  2, 3, 4, 4 };
    Mat exp = { 80, 118, 126, 97,
                44, 66, 85, 64,
                68, 100, 138, 88,
                38, 48, 68, 62 };

    Mat res = left * right;

    for (int i = 0; i < 16; i++)
        if (std::abs(exp.data[i] - res.data[i]) > 0.001)
            throw std::exception();
}

void test_camera_projection(Camera cam, Vec point, Vec projection)
{
    update_transformation(cam);
    recalc_mvp(cam, make_mat_id());

    Vec result = project_point(cam, point);

    if (std::abs(length(result - projection)) > 0.001)
        throw std::exception();
}

void test_camera()
{
    Camera cam = make_camera(60 * PI_2, 1, 10);
    Vec projection = make_pos(0, 0, 8.0 / 9);

    Vec point = make_pos(0, 0, 5);
    test_camera_projection(cam, point, projection);

    cam.yaw -= PI_2;
    point = make_pos(-5, 0, 0);
    test_camera_projection(cam, point, projection);
}

void test_ray_sphere_intersection()
{
    Ray ray = make_ray(make_pos(-10, 0, 0), make_dir(1, 0, 0));
    Sphere sphere = make_sphere(make_pos(0, 0, 0), 1);

    double t;
    if (!ray_intersects(t, ray, sphere))
        throw std::exception();

    if (std::abs(t - 9.0) > 0.001)
        throw std::exception();
}

void test_ray_plane_intersection()
{
    Ray ray = make_ray(make_pos(-10, 0, 0), make_dir(1, 0, 0));
    Plane plane = make_plane(make_pos(1, 1, 1), make_dir(-1, 0, 0));

    double t;
    if (!ray_intersects(t, ray, plane))
        throw std::exception();

    if (std::abs(t - 11) > 0.001)
        throw std::exception();

    plane.normal = -plane.normal;

    if (!ray_intersects(t, ray, plane))
        throw std::exception();

    if (std::abs(t - 11) > 0.001)
        throw std::exception();
}

void test_ray_face_intersection()
{
    Ray ray = make_ray(make_pos(-10, 0, 0), make_dir(1, 0, 0));
    Face face = make_face(
            make_vertex(make_pos(0, 1, 0)),
            make_vertex(make_pos(0, 0, 1)),
            make_vertex(make_pos(0, -1, -1))
            );

    double t;
    if (!ray_intersects(t, ray, face))
        throw std::exception();

    if (std::abs(t - 10) > 0.001)
        throw std::exception();
}

void test_rays()
{
    test_ray_sphere_intersection();
    test_ray_plane_intersection();
    test_ray_face_intersection();
}

int main()
{
    test_mat_mult();
    test_camera();
    test_rays();

    return 0;
}
