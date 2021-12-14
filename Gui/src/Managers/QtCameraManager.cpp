#include "QtCameraManager.hpp"


QtCameraManager::QtCameraManager(IManagerFactory &factory)
    : CameraManager(factory)
{
}

void QtCameraManager::onActiveCameraSwitch(std::shared_ptr<IObject> activeCamera)
{
    CameraManager::onActiveCameraSwitch(activeCamera);

    emit activeCameraSwitchSignal(activeCamera);
}

void QtCameraManager::onCameraChange(std::shared_ptr<IObject> camera)
{
    CameraManager::onCameraChange(camera);

    emit cameraChangeSignal(camera);
}
