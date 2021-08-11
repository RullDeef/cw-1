#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <memory>
#include <list>
#include "Objects/IObject.hpp"
#include "Scene/Scene.hpp"
#include "Managers/IManager.hpp"


class SceneManager : public IManager
{
public:
    explicit SceneManager(IManagerFactory& factory);

    void addScene(const std::shared_ptr<Scene>& scene);
    void removeScene(const std::shared_ptr<Scene>& scene);

    void setActiveScene(const std::shared_ptr<Scene>& scene);
    Scene& getActiveScene();

    void addObject(const std::shared_ptr<IObject>& object);
    void removeObject(std::shared_ptr<IObject> object);
    void removeObject(size_t objectId);

    void triggerSceneChanged();

protected:
    virtual void onAddScene(std::shared_ptr<Scene> scene);
    virtual void onBeforeRemoveScene(std::shared_ptr<Scene> scene);

    virtual void onActiveSceneChange(std::shared_ptr<Scene> scene);

    virtual void onAddObject(std::shared_ptr<IObject> object);
    virtual void onBeforeRemoveObject(std::shared_ptr<IObject> object);

private:
    std::list<std::shared_ptr<Scene>> scenes;
    std::list<std::shared_ptr<Scene>>::iterator activeScene;
};


#endif // SCENEMANAGER_HPP
