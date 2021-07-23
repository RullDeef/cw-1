#ifndef MANAGERFACTORY_HPP
#define MANAGERFACTORY_HPP

#include <memory>

class SceneManager;
class LoadManager;
class RenderManager;


class IManagerFactory
{
public:
    virtual ~IManagerFactory() = default;

    virtual std::shared_ptr<SceneManager> getSceneManager();
    virtual std::shared_ptr<RenderManager> getRenderManager();
    virtual std::shared_ptr<LoadManager> getLoadManager() = 0;

private:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<RenderManager> renderManager;
};

#endif // MANAGERFACTORY_HPP
