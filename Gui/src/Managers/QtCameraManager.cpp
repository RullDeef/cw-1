#include "QtCameraManager.hpp"


QtCameraManager::QtCameraManager(IManagerFactory &factory)
    : CameraManager(factory)
{
}

void QtCameraManager::onActiveCameraSwitch(Camera &activeCamera)
{
    emit activeCameraSwitchSignal(activeCamera);
}

void QtCameraManager::onCameraChange(Camera &camera)
{
    emit cameraChangeSignal(camera);
}
