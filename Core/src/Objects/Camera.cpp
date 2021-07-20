#include "Camera.hpp"
#include <algorithm>

using namespace Core;


Camera Core::make_camera(const Rect& viewport, double fov, double near, double far)
{
    Camera cam;

    cam.viewport = viewport;
    cam.model_mat = make_mat_id();
    cam.proj_mat = make_mat_perspective(fov, near, far);

    return cam;
}

void Core::recalc_mvp(Camera& camera)
{
    camera.mvp = camera.proj_mat * camera.model_mat;
}

Vec Core::project_point(const Camera& camera, const Vec& pos)
{
    Vec res = camera.mvp * pos;

    res.x /= res.z;
    res.y /= res.z;
    res.z = res.w;
    res.w = 1.0;

    double vmin2 = std::min(camera.viewport.width, camera.viewport.height) / 2;
    res.x = camera.viewport.left + res.x * vmin2 + camera.viewport.width / 2;
    res.y = camera.viewport.top - res.y * vmin2 + camera.viewport.height / 2;

    return res;
}
