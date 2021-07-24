#include "IManagerFactory.hpp"
#include "SceneManager.hpp"
#include "RenderManager.hpp"
#include "LoadManager.hpp"
#include "CameraManager.hpp"


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
