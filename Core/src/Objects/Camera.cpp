#include "Camera.hpp"

using namespace Core;


Camera Core::make_camera(double fov, double near, double far)
{
    Camera cam;

    cam.model_mat = mat_identity();
    cam.fov = fov;
    cam.near = near;
    cam.far = far;

    return cam;
}

mat Core::get_camera_mat(const Camera& camera, int vwidth, int vheight)
{
    double aspect = static_cast<double>(vwidth) / vheight;
    mat proj_mat = mat_perspective(camera.fov, aspect, camera.near, camera.far);

    return mat_mult(camera.model_mat, proj_mat);
}
