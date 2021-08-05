#include "QtSceneManager.hpp"


QtSceneManager::QtSceneManager(IManagerFactory &factory)
    : SceneManager(factory)
{
}

void QtSceneManager::onAddScene(std::shared_ptr<Scene> scene)
{
    emit addSceneSignal(scene);
}

void QtSceneManager::onActiveSceneChange(std::shared_ptr<Scene> scene)
{
    emit activeSceneChangeSignal(scene);
}

void QtSceneManager::onAddObject(std::shared_ptr<IObject> object)
{
    emit addObjectSignal(object);
}
