#define _USE_MATH_DEFINES
#include <cmath>
#include "Objects/Adapters/CameraAdapter.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/CameraManager.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/RenderManager.hpp"
#include "Managers/SelectionManager.hpp"


CameraManager::CameraManager(IManagerFactory &factory)
    : IManager(factory), defaultCamera(new ObjectAdapter<Camera>(0,
        Camera(Vector(0, 0, 400, 1), 0, 0)))
{
    /// TODO: get rid of z=400 constant
}

void CameraManager::switchToFirstCamera()
{
    sceneCamera = nullptr;

    auto& scene = getFactory().getSceneManager()->getActiveScene();
    for (const auto& obj : scene)
    {
        if (dynamic_cast<ObjectAdapter<Camera>*>(obj.get()))
        {
            sceneCamera = obj;
            break;
        }
    }
}

void CameraManager::switchToSelectedCamera()
{
    sceneCamera = nullptr;

    auto selection = getFactory().getSelectionManager()->getSelectedObjects();
    for (const auto& obj : selection)
    {
        if (dynamic_cast<ObjectAdapter<Camera>*>(obj.get()) != nullptr)
        {
            sceneCamera = obj;
            break;
        }
    }
}

std::shared_ptr<IObject> CameraManager::getActiveCamera()
{
    if (sceneCamera && dynamic_cast<ObjectAdapter<Camera>*>(sceneCamera.get()))
        return sceneCamera;

    return defaultCamera;
}

void CameraManager::rotateCamera(double dx, double dy)
{
    /// TODO: make dPitch dYaw depend on viewport
    auto adapter = getActiveCamera();
    auto& camera = dynamic_cast<ObjectAdapter<Camera>*>(adapter.get())->getAdaptee();

    // camera.rotate(dy, dx);

    double x = camera.getPitch() + dy;
    double y = camera.getYaw() + dx;
    adapter->setRotation(Vector(x, y, 0, 0) * 180 / M_PI); /// TODO: move logic in camera adapter

    onCameraChange(adapter);
}

void CameraManager::zoomCamera(double factor)
{

}

void CameraManager::freeFlyCamera(double forward, double right, double up)
{
    auto adapter = getActiveCamera();
    auto& camera = dynamic_cast<ObjectAdapter<Camera>*>(adapter.get())->getAdaptee();

    auto offset = camera.getModelMatrix() * Vector(right, up, forward, 0);

    adapter->setPosition(adapter->getPosition() + offset);
}

Ray CameraManager::createRay(int x, int y)
{
    Rect viewport = getFactory().getRenderManager()->getActiveViewport();
    Vector uPos = viewport.outerQuad(float(x), float(y));

    auto& camera = dynamic_cast<ObjectAdapter<Camera>*>(getActiveCamera().get())->getAdaptee();
    return camera.createRay(uPos.getX(), uPos.getY(), viewport);
}

void CameraManager::onActiveCameraSwitch(std::shared_ptr<IObject> activeCamera)
{
    getFactory().getRenderManager()->renderActiveScene();
}

void CameraManager::onCameraChange(std::shared_ptr<IObject> camera)
{
    getFactory().getRenderManager()->renderActiveScene();
}
