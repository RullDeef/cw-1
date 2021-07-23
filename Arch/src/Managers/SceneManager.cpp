#include <utility>
#include "IManagerFactory.hpp"
#include "SceneManager.hpp"


SceneManager::SceneManager(IManagerFactory& factory)
    : IManager(factory), activeScene(std::make_shared<Scene>())
{
}

std::shared_ptr<Scene> SceneManager::getActiveScene()
{
    return activeScene;
}
