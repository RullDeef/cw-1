#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/RenderManager.hpp"
#include "Managers/LoadManager.hpp"
#include "Managers/CameraManager.hpp"
#include "Managers/ObjectManager.hpp"


std::shared_ptr<SceneManager> IManagerFactory::getSceneManager()
{
    if (!sceneManager)
        sceneManager = std::make_shared<SceneManager>(*this);
    return sceneManager;
}

std::shared_ptr<RenderManager> IManagerFactory::getRenderManager()
{
    if (!renderManager)
        renderManager = std::make_shared<RenderManager>(*this);
    return renderManager;
}

std::shared_ptr<CameraManager> IManagerFactory::getCameraManager()
{
    if (!cameraManager)
        cameraManager = std::make_shared<CameraManager>(*this);
    return cameraManager;
}

std::shared_ptr<ObjectManager> IManagerFactory::getObjectManager()
{
    if (!objectManager)
        objectManager = std::make_shared<ObjectManager>(*this);
    return objectManager;
}
