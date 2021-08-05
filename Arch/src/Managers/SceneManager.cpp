#include <utility>
#include <algorithm>
#include <stdexcept>
#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"


SceneManager::SceneManager(IManagerFactory& factory)
    : IManager(factory), activeScene(scenes.end())
{
}

void SceneManager::addScene(const std::shared_ptr<Scene>& scene)
{
    scenes.push_back(scene);
    onAddScene(scene);
}

void SceneManager::removeScene(const std::shared_ptr<Scene>& scene)
{
    if (std::find(scenes.begin(), scenes.end(), scene) != scenes.end())
    {
        onBeforeRemoveScene(scene);
        scenes.remove(scene);
    }
}

void SceneManager::setActiveScene(const std::shared_ptr<Scene>& scene)
{
    auto iter = std::find(scenes.begin(), scenes.end(), scene);
    if (iter != scenes.end())
    {
        activeScene = iter;
        onActiveSceneChange(scene);
    }
}

Scene& SceneManager::getActiveScene()
{
    if (activeScene == scenes.end())
        throw std::runtime_error("bad scene pointer");
    return **activeScene;
}

void SceneManager::addObject(const std::shared_ptr<IObject>& object)
{
    auto scene = getActiveScene();
    scene.insert(scene.end(), object);
    onAddObject(object);
}

void SceneManager::onAddScene(std::shared_ptr<Scene> scene)
{
}

void SceneManager::onBeforeRemoveScene(std::shared_ptr<Scene> scene)
{
}

void SceneManager::onActiveSceneChange(std::shared_ptr<Scene> scene)
{
}

void SceneManager::onAddObject(std::shared_ptr<IObject> object)
{
}

void SceneManager::onBeforeRemoveObject(std::shared_ptr<IObject> object)
{
}
