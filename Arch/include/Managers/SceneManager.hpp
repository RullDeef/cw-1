#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <memory>
#include "Scene/Scene.hpp"
#include "Managers/IManager.hpp"


class SceneManager : public IManager
{
public:
    explicit SceneManager(IManagerFactory& factory);

    std::shared_ptr<Scene> getActiveScene();

private:
    std::shared_ptr<Scene> activeScene;
};


#endif // SCENEMANAGER_HPP
