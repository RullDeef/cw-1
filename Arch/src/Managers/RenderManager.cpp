#include <chrono>
#include "Core.hpp"
#include "RenderManager.hpp"
#include "IManagerFactory.hpp"
#include "SceneManager.hpp"
#include "ObjectAdapter.hpp"
#include "CameraManager.hpp"


RenderManager::RenderManager(IManagerFactory &factory)
        : IManager(factory)
{
}

void RenderManager::renderScene(Core::RenderTarget &renderTarget)
{
    Core::Scene scene = requireScene();

    Core::Rect viewport = Core::make_rect(renderTarget.width, renderTarget.height);
    Core::Camera camera = requireCamera(viewport);

    Core::renderScene({
                              renderTarget, scene, camera,
                              Core::RenderParams::RenderType::FastRenderType,
                              viewport
                      });
}

Core::Camera RenderManager::requireCamera(const Core::Rect &viewport)
{
    Core::Camera camera = getFactory().getCameraManager()->getActiveCamera().getAdaptee();

    Core::update_viewport(camera, viewport);

    //camera.model_mat = Core::make_mat_translation(Core::make_pos(50, -100, -400));

    Core::recalc_mvp(camera);
    return camera;
}

Core::Scene RenderManager::requireScene()
{
    Core::Scene scene = getFactory().getSceneManager()->getActiveScene()->getRawScene();
    return scene;
}
