#include "Managers/CameraManager.hpp"


CameraManager::CameraManager(IManagerFactory &factory)
    : IManager(factory), mainCamera(-1, Core::make_camera(), AdapterPolicy::WeakOwnership)
{
    mainCamera.getAdaptee().
    eye = Core::make_pos(-50, 100, 400);
    Core::update_transformation(mainCamera.getAdaptee());
}

ObjectAdapter<Core::Camera> &CameraManager::getActiveCamera()
{
    return mainCamera;
}

const ObjectAdapter<Core::Camera> &CameraManager::getActiveCamera() const
{
    return mainCamera;
}

void CameraManager::dragCamera(double dx, double dy)
{
    Core::Camera& cam = getActiveCamera().getAdaptee();

    Core::Vec offset = Core::make_dir(dx, -dy, 0);
    offset = cam.model_mat * offset;
    cam.eye = cam.eye + offset;

    Core::update_transformation(cam);
}

void CameraManager::rotateCamera(double dx, double dy)
{
    Core::Camera& cam = getActiveCamera().getAdaptee();

    double d_yaw = -dx;
    double d_pitch = -dy;

    cam.pitch += d_pitch;
    cam.yaw += d_yaw;

    if (cam.pitch < -3.141592 / 2)
        cam.pitch = -3.141592 / 2;
    if (cam.pitch > 3.141592 / 2)
        cam.pitch = 3.141592 / 2;

    Core::update_transformation(cam);
}

void CameraManager::zoomCamera(double factor)
{

}

void CameraManager::freeFlyCamera(double forward, double right, double up)
{
    Core::Camera& cam = getActiveCamera().getAdaptee();

    Core::Vec offset = Core::make_dir(right, up, -forward);
    offset = cam.model_mat * offset;
    cam.eye = cam.eye + offset;

    Core::update_transformation(cam);
}

Core::Ray CameraManager::createRay(int x, int y)
{
    Core::Camera& cam = getActiveCamera().getAdaptee();

    Core::Vec pos = cam.eye;
    Core::Vec dir = Core::make_dir(0, 0, 1); /// TODO: implement

    return Core::make_ray(pos, dir);
}
