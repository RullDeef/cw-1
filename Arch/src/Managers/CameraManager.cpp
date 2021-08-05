#define _USE_MATH_DEFINES
#include <cmath>
#include "Managers/CameraManager.hpp"


CameraManager::CameraManager(IManagerFactory &factory)
    : IManager(factory)
{
    // TODO: refactor
    Core::Camera cam = mainCamera;
    cam.eye = Core::make_pos(0, 100, 400);
    cam.yaw = M_PI;
    Core::update_transformation(cam);
}

Camera& CameraManager::getActiveCamera()
{
    return mainCamera;
}

void CameraManager::dragCamera(double dx, double dy)
{
    Core::Camera cam = getActiveCamera();

    Core::Vec offset = Core::make_dir(dx, -dy, 0);
    offset = cam.model_mat * offset;
    cam.eye = cam.eye + offset;

    Core::update_transformation(cam);
}

void CameraManager::rotateCamera(double dx, double dy)
{
    Core::Camera cam = getActiveCamera();

    double d_yaw = dx;
    double d_pitch = dy;

    cam.pitch += d_pitch;
    cam.yaw += d_yaw;

    if (cam.pitch < -M_PI_2)
        cam.pitch = -M_PI_2;
    if (cam.pitch > M_PI_2)
        cam.pitch = M_PI_2;

    Core::update_transformation(cam);
}

void CameraManager::zoomCamera(double factor)
{

}

void CameraManager::freeFlyCamera(double forward, double right, double up)
{
    Core::Camera cam = getActiveCamera();

    Core::Vec offset = Core::make_dir(right, up, forward);
    offset = cam.model_mat * offset;
    cam.eye = cam.eye + offset;

    Core::update_transformation(cam);
}

Core::Ray CameraManager::createRay(int x, int y)
{
    Core::Camera cam = getActiveCamera();

    double max_v = std::max(cam.viewport.width, cam.viewport.height);

    double dir_x = (2 * x - cam.viewport.width) / max_v;
    double dir_y = (cam.viewport.height - 2 * y) / max_v;
    double dir_z = 1.0 / std::tan(cam.fov / 2);

    Core::Vec pos = cam.eye;
    Core::Vec dir = Core::make_dir(dir_x, dir_y, dir_z);
    Core::normalize(dir);

    Core::Mat view = cam.model_mat;
    dir = view * dir;

    return Core::make_ray(pos, dir);
}

void CameraManager::onActiveCameraSwitch(Camera& activeCamera)
{
}

void CameraManager::onCameraChange(Camera& camera)
{
}
