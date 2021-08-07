#include "QtSceneManager.hpp"


QtSceneManager::QtSceneManager(IManagerFactory &factory)
    : SceneManager(factory)
{
}

void QtSceneManager::onAddScene(std::shared_ptr<Scene> scene)
{
    SceneManager::onAddScene(scene);

    emit addSceneSignal(scene);
}

void QtSceneManager::onActiveSceneChange(std::shared_ptr<Scene> scene)
{
    SceneManager::onActiveSceneChange(scene);

    emit activeSceneChangeSignal(scene);
}

void QtSceneManager::onAddObject(std::shared_ptr<IObject> object)
{
    SceneManager::onAddObject(object);

    emit addObjectSignal(object);
}
