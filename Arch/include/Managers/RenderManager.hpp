#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "RenderTarget/RenderTarget.hpp"
#include "Objects/Camera.hpp"
#include "Scene/Scene.hpp"
#include "IManager.hpp"
#include "Math/Rect.hpp"
#include "RenderSettings/RenderSettings.hpp"
#include "Threading/ThreadPool.hpp"


class RenderManager : public IManager
{
public:
    explicit RenderManager(IManagerFactory& factory);

    void renderActiveScene();
    void renderActiveScene(const RenderSettings& renderSettings);

    inline double getRenderPercent() const { return renderPercent; }

    virtual Rect getActiveViewport() = 0;

protected:
    void renderScene(Scene &scene, Camera &camera, const RenderSettings& renderSettings);
    void renderOverlay(Scene &scene, Camera &camera, const RenderSettings& renderSettings);

    virtual RenderTarget getSceneRenderTarget() = 0;
    virtual RenderTarget getOverlayRenderTarget() = 0;

    virtual void onBeforeSceneRender(Scene &scene, Camera &camera, const RenderSettings &renderSettings);
    virtual void onSceneRender(Scene &scene, Camera &camera, const RenderSettings &renderSettings);

private:
    double renderPercent;
};

#endif // RENDERMANAGER_HPP
