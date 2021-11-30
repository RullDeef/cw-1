#define _USE_MATH_DEFINES
#include <cmath>
#include "Managers/CameraManager.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/RenderManager.hpp"


CameraManager::CameraManager(IManagerFactory &factory)
    : IManager(factory), mainCamera(Vector(0, 0, 400, 1), 0, 0)
{
    ///TODO: get rid of z=400 constant
}

Camera& CameraManager::getActiveCamera()
{
    return mainCamera;
}

void CameraManager::rotateCamera(double dx, double dy)
{
    /// TODO: make dPitch dYaw depend on viewport
    getActiveCamera().rotate(dy, dx);

    onCameraChange(getActiveCamera());
}

void CameraManager::zoomCamera(double factor)
{

}

void CameraManager::freeFlyCamera(double forward, double right, double up)
{
    auto offset = getActiveCamera().getModelMatrix() * Vector(right, up, forward, 0);
    getActiveCamera().translate(offset);
}

Ray CameraManager::createRay(int x, int y)
{
    Rect viewport = getFactory().getRenderManager()->getActiveViewport();
    Vector uPos = viewport.outerQuad(x, y);

    return getActiveCamera().createRay(uPos.getX(), uPos.getY(), viewport);
}

void CameraManager::onActiveCameraSwitch(Camera& activeCamera)
{
    getFactory().getRenderManager()->renderActiveScene();
}

void CameraManager::onCameraChange(Camera& camera)
{
    getFactory().getRenderManager()->renderActiveScene();
}
