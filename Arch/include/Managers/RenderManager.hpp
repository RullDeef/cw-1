#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "Objects/Camera.hpp"
#include "Scene/Scene.hpp"
#include "IManager.hpp"

/// TODO: implement renderTarget wrapper
class RenderTarget;


class RenderManager : public IManager
{
public:
    explicit RenderManager(IManagerFactory& factory);

    void renderActiveScene();

protected:
    void renderScene(Scene &scene, Camera &camera);

    virtual RenderTarget getRenderTarget() = 0;

    virtual void onBeforeSceneRender(Scene& scene, Camera& camera);
    virtual void onSceneRender(Scene& scene, Camera& camera);
};

#endif // RENDERMANAGER_HPP
