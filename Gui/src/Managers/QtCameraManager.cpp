#include "QtCameraManager.hpp"


QtCameraManager::QtCameraManager(IManagerFactory &factory)
    : CameraManager(factory)
{
}

void QtCameraManager::onActiveCameraSwitch(Camera &activeCamera)
{
    CameraManager::onActiveCameraSwitch(activeCamera);

    emit activeCameraSwitchSignal(activeCamera);
}

void QtCameraManager::onCameraChange(Camera &camera)
{
    CameraManager::onCameraChange(camera);

    emit cameraChangeSignal(camera);
}
