#ifndef CAMERAMANAGER_HPP
#define CAMERAMANAGER_HPP

#include "Core/common/math/Ray.hpp"
#include "Objects/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Managers/IManager.hpp"


class CameraManager : public IManager
{
public:
    explicit CameraManager(IManagerFactory& factory);

    Camera& getActiveCamera();

    // translates camera along view plane
    void dragCamera(double dx, double dy);

    // rotates camera around itself (or around selected object?)
    void rotateCamera(double dx, double dy);

    // zoomIn & zoomOut (wheel up/down)
    void zoomCamera(double factor);

    void freeFlyCamera(double forward, double right, double up);

    Core::Ray createRay(int x, int y); /// TODO: make Ray class

protected:
    virtual void onActiveCameraSwitch(Camera& activeCamera);
    virtual void onCameraChange(Camera& camera);

private:
    Camera mainCamera;
};

#endif // CAMERAMANAGER_HPP
