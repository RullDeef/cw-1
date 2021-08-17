#ifndef MANAGERFACTORY_HPP
#define MANAGERFACTORY_HPP

#include <memory>

class SceneManager;
class LoadManager;
class RenderManager;
class CameraManager;
class SelectionManager;
class SettingsManager;


/// TODO: сделать менеджер ввода. (Настройки клавиш + FreeFlyDispatcher)

class IManagerFactory
{
public:
    virtual ~IManagerFactory() = default;

    virtual std::shared_ptr<SceneManager> getSceneManager() = 0;
    virtual std::shared_ptr<CameraManager> getCameraManager() = 0;
    virtual std::shared_ptr<RenderManager> getRenderManager() = 0;
    virtual std::shared_ptr<LoadManager> getLoadManager() = 0;
    virtual std::shared_ptr<SelectionManager> getSelectionManager() = 0;
    virtual std::shared_ptr<SettingsManager> getSettingsManager() = 0;
};

#endif // MANAGERFACTORY_HPP
