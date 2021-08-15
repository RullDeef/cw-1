#define _USE_MATH_DEFINES
#include <cmath>
#include "Managers/CameraManager.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/RenderManager.hpp"


CameraManager::CameraManager(IManagerFactory &factory)
    : IManager(factory), mainCamera(Vector(0, 100, 400), 0, M_PI)
{
}

Camera& CameraManager::getActiveCamera()
{
    return mainCamera;
}

void CameraManager::dragCamera(double dx, double dy)
{
    /// TODO: make offset vector depend on distance to observable
    getActiveCamera().translate(Vector(dx, -dy, 0));
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
    getActiveCamera().translate(Vector(right, up, forward, 0));
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
