#include <utility>
#include "Objects/IObject.hpp"
#include "Loaders/ILoader.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/LoadManager.hpp"


LoadManager::LoadManager(IManagerFactory& factory)
    : IManager(factory)
{
}

void LoadManager::loadScene()
{
    std::string filename = requestFilename();
    std::shared_ptr<Scene> scene = loader->loadScene();

    auto sceneManager = getFactory().getSceneManager();
    sceneManager->addScene(scene);
    sceneManager->setActiveScene(scene);

    onSceneLoad(scene);
}

void LoadManager::setLoader(std::shared_ptr<ILoader> newLoader)
{
    loader = std::move(newLoader);
}

void LoadManager::onSceneLoad(std::shared_ptr<Scene> scene)
{
}

void LoadManager::onObjectLoad(std::shared_ptr<IObject> object)
{
}
