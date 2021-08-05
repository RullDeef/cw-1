#include <chrono>
#include <vector>
#include <future>
#include "Core/Core.hpp"
#include "Objects/ObjectAdapter.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/CameraManager.hpp"
#include "Managers/RenderManager.hpp"


RenderManager::RenderManager(IManagerFactory &factory)
        : IManager(factory)
{
}

void RenderManager::renderActiveScene()
{
    auto scene = getFactory().getSceneManager()->getActiveScene();
    auto camera = getFactory().getCameraManager()->getActiveCamera();

    onBeforeSceneRender(scene, camera);
    renderScene(scene, camera);
    onSceneRender(scene, camera);
}

void RenderManager::renderScene(Scene &scene, Camera &camera)
{
    auto renderTarget = getRenderTarget();
    Core::Rect viewport = renderTarget.getViewport(); // Core::make_rect(renderTarget.width, renderTarget.height);
    camera.updateViewport(viewport);

    Core::renderScene({
        renderTarget, scene, camera,
        Core::RenderParams::RenderType::FastRenderType,
        viewport
    });
}

void RenderManager::onBeforeSceneRender(Scene &scene, Camera &camera)
{
}

void RenderManager::onSceneRender(Scene &scene, Camera &camera)
{
}
