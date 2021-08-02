#ifndef CAMERAMANAGER_HPP
#define CAMERAMANAGER_HPP

#include "Core/common/math/Ray.hpp"
#include "Core/Objects/Camera.hpp"
#include "Objects/ObjectAdapter.hpp"
#include "Scene/Scene.hpp"
#include "Managers/IManager.hpp"


class CameraManager : public IManager
{
public:
    explicit CameraManager(IManagerFactory& factory);

    ObjectAdapter<Core::Camera>& getActiveCamera();
    const ObjectAdapter<Core::Camera>& getActiveCamera() const;

    // translates camera along view plane
    void dragCamera(double dx, double dy);

    // rotates camera around itself (or around selected object?)
    void rotateCamera(double dx, double dy);

    // zoomIn & zoomOut (wheel up/down)
    void zoomCamera(double factor);

    void freeFlyCamera(double forward, double right, double up);

    Core::Ray createRay(int x, int y);

private:
    Scene::iterator cameraIterator;
    ObjectAdapter<Core::Camera> mainCamera;
};

#endif // CAMERAMANAGER_HPP
