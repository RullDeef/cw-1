#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <memory>
#include "Objects/IObject.hpp"
#include "Scene/Scene.hpp"
#include "Managers/IManager.hpp"


class SceneManager : public IManager
{
public:
    explicit SceneManager(IManagerFactory& factory);

    std::shared_ptr<Scene> getActiveScene();

    void addObject(std::shared_ptr<IObject> object);

private:
    std::shared_ptr<Scene> activeScene;
};


#endif // SCENEMANAGER_HPP
