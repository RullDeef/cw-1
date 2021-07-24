//
// Created by rulldeef on 7/24/21.
//

#include "CameraManager.hpp"

CameraManager::CameraManager(IManagerFactory &factory)
    : IManager(factory), mainCamera(-1, Core::make_camera(), AdapterPolicy::WeakOwnership)
{
    mainCamera.getAdaptee().model_mat = Core::make_mat_translation(0, 0, -300);
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
    Core::Mat transform = Core::make_mat_translation(dx, dy, 0);

    cam.model_mat = transform * cam.model_mat;
}

void CameraManager::rotateCamera(double dx, double dy)
{
    Core::Camera& cam = getActiveCamera().getAdaptee();
    Core::Mat transform =
            Core::make_mat_rotation(Core::make_dir(1, 0, 0), dy)
            * Core::make_mat_rotation(Core::make_dir(0, 1, 0), dx);

    cam.model_mat = transform * cam.model_mat;
}

void CameraManager::zoomCamera(double factor)
{

}
