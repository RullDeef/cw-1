#include <chrono>
#include <vector>
#include <future>
#include "Core/Core.hpp"
#include "Objects/ObjectAdapter.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/CameraManager.hpp"
#include "Managers/RenderManager.hpp"
#include "Managers/SettingsManager.hpp"


RenderManager::RenderManager(IManagerFactory &factory)
        : IManager(factory)
{
}

void RenderManager::renderActiveScene()
{
    auto settings = getFactory().getSettingsManager()->getRenderSettings();
    renderActiveScene(settings);
}

void RenderManager::renderActiveScene(const RenderSettings& renderSettings)
{
    try
    {
        Scene& scene = getFactory().getSceneManager()->getActiveScene();
        auto camera = getFactory().getCameraManager()->getActiveCamera();

        onBeforeSceneRender(scene, camera, renderSettings);
        renderScene(scene, camera, renderSettings);
        renderOverlay(scene, camera, renderSettings);
        onSceneRender(scene, camera, renderSettings);
    }
    catch (...)
    {
    }
}

void RenderManager::renderScene(Scene &scene, Camera &camera, const RenderSettings& renderSettings)
{
    Core::RenderParams params = Core::make_render_params(getSceneRenderTarget(), scene, camera);
    renderSettings.applyTo(params);
    Core::renderScene(params);
}

void RenderManager::renderOverlay(Scene &scene, Camera &camera, const RenderSettings& renderSettings)
{
    auto params = Core::make_render_params(getOverlayRenderTarget(), scene, camera);
    renderSettings.applyTo(params);
    params.renderType = Core::RenderType::Overlay;
    Core::renderScene(params);
}

void RenderManager::onBeforeSceneRender(Scene &scene, Camera &camera, const RenderSettings &renderSettings)
{
}

void RenderManager::onSceneRender(Scene &scene, Camera &camera, const RenderSettings &renderSettings)
{
}
