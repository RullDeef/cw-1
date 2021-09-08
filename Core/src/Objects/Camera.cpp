#include "Core/Objects/Camera.hpp"
#include <algorithm>

using namespace Core;


Camera Core::make_camera(double fov, double near, double far)
{
    Camera cam{};

    cam.fov = fov;
    cam.near = near;
    cam.far = far;
    cam.eye = make_pos();
    cam.pitch = .0;
    cam.yaw = .0;

    cam.model_mat = make_mat_id();
    cam.proj_mat = make_mat_perspective(fov, near, far);

    return cam;
}

void Core::update_viewport(Camera& camera, const Rect& viewport)
{
    camera.viewport = viewport;
}

void Core::recalc_mvp(Camera& camera, const Mat& model_mat)
{
    camera.mvp = camera.proj_mat * inverse(camera.model_mat) * model_mat;
}

Vec Core::project_viewport_frustrum(const Camera& camera, const Vec& point)
{
    Vec res = camera.mvp * point;

    res.x *= get_x_aspect(camera.viewport);
    res.y *= get_y_aspect(camera.viewport);

//    if (camera.viewport.width > camera.viewport.height)
//        res.y *= double(camera.viewport.height) / camera.viewport.width;
//    else
//        res.x *= double(camera.viewport.width) / camera.viewport.height;

    return res;
}

Vec Core::adjust(const Camera& camera, const Vec& pos)
{
    Vec res = pos;

    if (camera.viewport.width > camera.viewport.height)
        res.y /= double(camera.viewport.height) / camera.viewport.width;
    else
        res.x /= double(camera.viewport.width) / camera.viewport.height;

    return viewport_adjust(camera, res);
}

Vec Core::project_frustrum(const Camera& camera, const Vec& pos)
{
    return camera.mvp * pos;
}

Vec Core::viewport_adjust(const Camera& camera, const Vec& pos)
{
    Vec res = pos;
    perspective_adjust(res);

    // TODO: возможно стоит вынести все махинации с вьюпортом в отдельные функции в Rect.hpp
#if USE_MIN_FIT
    double vmin2 = std::min<double>(camera.viewport.width, camera.viewport.height) / 2;
    res.x = camera.viewport.left + res.x * vmin2 + camera.viewport.width / 2;
    res.y = camera.viewport.top - res.y * vmin2 + camera.viewport.height / 2;
#else
    double vmax2 = std::max<double>(camera.viewport.width, camera.viewport.height) / 2;
    res.x = camera.viewport.left + res.x * vmax2 + double(camera.viewport.width) / 2;
    res.y = camera.viewport.top - res.y * vmax2 + double(camera.viewport.height) / 2;

    /// not working
    // Rect outer_box = get_outer_box(camera.viewport);
    // Rect unit_box = make_rect(2, -2, -1, -1);
    // res = map_point(unit_box, outer_box, res);
#endif

    return res;
}

Vec Core::unproject_frustrum(const Camera& camera, const Vec& pos)
{
    return inverse(camera.mvp) * pos;
}

Vec Core::project_point(const Camera& camera, const Vec& pos)
{
    Vec res = project_frustrum(camera, pos);
    return viewport_adjust(camera, res);
}

Ray Core::shoot_ray(const Camera& camera, int x, int y)
{
    double z = 1.0 / std::tan(camera.fov / 2);

    Vec dir = outer_quad(camera.viewport, x, y);
    dir.z = z;
    dir = camera.model_mat * normalized(dir);

    return make_ray(camera.eye, dir);
}

void Core::update_transformation(Camera &camera)
{
    double cosPitch = std::cos(camera.pitch);
    double sinPitch = std::sin(camera.pitch);
    double cosYaw = std::cos(camera.yaw);
    double sinYaw = std::sin(camera.yaw);

    Vec x_axis = make_dir(cosYaw, 0, -sinYaw);
    Vec y_axis = make_dir(sinYaw * sinPitch, cosPitch, cosYaw * sinPitch);
    Vec z_axis = make_dir(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

    camera.model_mat = inverse({
            x_axis.x, x_axis.y, x_axis.z, -dot(x_axis, camera.eye),
            y_axis.x, y_axis.y, y_axis.z, -dot(y_axis, camera.eye),
            z_axis.x, z_axis.y, z_axis.z, -dot(z_axis, camera.eye),
            0, 0, 0, 1
    });
}
