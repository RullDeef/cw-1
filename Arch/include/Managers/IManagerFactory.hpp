#ifndef MANAGERFACTORY_HPP
#define MANAGERFACTORY_HPP

#include <memory>

class SceneManager;
class LoadManager;
class RenderManager;
class CameraManager;
class ObjectManager;


/// TODO: сделать менеджер ввода. (Настройки клавиш + FreeFlyDispatcher)

class IManagerFactory
{
public:
    virtual ~IManagerFactory() = default;

    virtual std::shared_ptr<SceneManager> getSceneManager();
    virtual std::shared_ptr<RenderManager> getRenderManager();
    virtual std::shared_ptr<LoadManager> getLoadManager() = 0;
    virtual std::shared_ptr<CameraManager> getCameraManager();
    virtual std::shared_ptr<ObjectManager> getObjectManager();

private:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<RenderManager> renderManager;
    std::shared_ptr<CameraManager> cameraManager;
    std::shared_ptr<ObjectManager> objectManager;
};

#endif // MANAGERFACTORY_HPP
