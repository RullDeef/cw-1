#include <utility>
#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"


SceneManager::SceneManager(IManagerFactory& factory)
    : IManager(factory), activeScene(std::make_shared<Scene>())
{
}

std::shared_ptr<Scene> SceneManager::getActiveScene()
{
    return activeScene;
}

void SceneManager::addObject(std::shared_ptr<IObject> object)
{
    auto scene = getActiveScene();
    scene->insert(scene->end(), object);
}
