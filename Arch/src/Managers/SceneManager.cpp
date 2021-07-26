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
