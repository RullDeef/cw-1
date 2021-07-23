#include "IManagerFactory.hpp"
#include "SceneManager.hpp"
#include "RenderManager.hpp"
#include "LoadManager.hpp"


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
