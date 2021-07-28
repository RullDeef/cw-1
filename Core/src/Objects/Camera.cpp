#include "Core/Objects/Camera.hpp"
#include <algorithm>

using namespace Core;


Camera Core::make_camera(double fov, double near, double far)
{
    Camera cam;

    cam.fov = fov;
    cam.near = near;
    cam.far = far;

    cam.model_mat = make_mat_id();
    cam.proj_mat = make_mat_perspective(fov, near, far);

    return cam;
}

void Core::update_viewport(Camera& camera, const Rect& viewport)
{
    camera.viewport = viewport;
}

void Core::recalc_mvp(Camera& camera)
{
    camera.mvp = camera.proj_mat * camera.model_mat;
}

/// TODO: fix this.
Vec Core::view_dir(const Camera &camera)
{
    return inverse(camera.model_mat) * Core::make_dir(0, 0, 1);
}

Vec Core::view_pos(const Camera& camera)
{
    return inverse(camera.model_mat) * Core::make_pos(0, 0, 0);
}

Vec Core::project_point(const Camera& camera, const Vec& pos)
{
    Vec res = camera.mvp * pos;

    res.x /= res.z;
    res.y /= res.z;
    res.z = res.w;
    res.w = 1.0;

    // TODO: возможно стоит вынести все махинации с вьюпортом в отдельные функции в Rect.hpp
#if USE_MIN_FIT
    double vmin2 = std::min<double>(camera.viewport.width, camera.viewport.height) / 2;
    res.x = camera.viewport.left + res.x * vmin2 + camera.viewport.width / 2;
    res.y = camera.viewport.top - res.y * vmin2 + camera.viewport.height / 2;
#else
    double vmax2 = std::max<double>(camera.viewport.width, camera.viewport.height) / 2;
    res.x = camera.viewport.left + res.x * vmax2 + double(camera.viewport.width) / 2;
    res.y = camera.viewport.top - res.y * vmax2 + double(camera.viewport.height) / 2;
#endif

    return res;
}
