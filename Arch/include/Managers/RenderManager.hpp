#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "RenderTarget/RenderTarget.hpp"
#include "Objects/Camera.hpp"
#include "Scene/Scene.hpp"
#include "IManager.hpp"
#include "Math/Rect.hpp"


class RenderManager : public IManager
{
public:
    explicit RenderManager(IManagerFactory& factory);

    void renderActiveScene();

    virtual Rect getActiveViewport() = 0;

protected:
    void renderScene(Scene &scene, Camera &camera);
    void renderOverlay(Scene &scene, Camera &camera);

    virtual RenderTarget getSceneRenderTarget() = 0;
    virtual RenderTarget getOverlayRenderTarget() = 0;

    virtual void onBeforeSceneRender(Scene& scene, Camera& camera);
    virtual void onSceneRender(Scene& scene, Camera& camera);
};

#endif // RENDERMANAGER_HPP
