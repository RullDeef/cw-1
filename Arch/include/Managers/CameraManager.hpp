#ifndef CAMERAMANAGER_HPP
#define CAMERAMANAGER_HPP

#include "Math/Ray.hpp"
#include "Objects/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Managers/IManager.hpp"


class CameraManager : public IManager
{
public:
    explicit CameraManager(IManagerFactory& factory);

    void switchToFirstCamera();
    void switchToSelectedCamera();

    std::shared_ptr<IObject> getActiveCamera();

    // translates camera along view plane
    void dragCamera(double dx, double dy);

    // rotates camera around itself (or around selected object?)
    void rotateCamera(double dx, double dy);

    // zoomIn & zoomOut (wheel up/down)
    void zoomCamera(double factor);

    void freeFlyCamera(double forward, double right, double up);

    Ray createRay(int x, int y);

protected:
    virtual void onActiveCameraSwitch(std::shared_ptr<IObject> activeCamera);
    virtual void onCameraChange(std::shared_ptr<IObject> camera);

private:
    std::shared_ptr<IObject> defaultCamera;
    std::shared_ptr<IObject> sceneCamera;
};

#endif // CAMERAMANAGER_HPP
