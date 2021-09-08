#include <chrono>
#include <sstream>
#include <iomanip>
#include "Core/Core.hpp"
#include "Objects/ObjectAdapter.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/CameraManager.hpp"
#include "Managers/RenderManager.hpp"
#include "Managers/SettingsManager.hpp"
#include "Managers/InfoManager.hpp"


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
    Core::RenderTarget renderTarget = getSceneRenderTarget();
    Core::RenderParams params = Core::make_render_params(renderTarget, scene, camera);
    renderSettings.applyTo(params);

    auto timeStart = std::chrono::high_resolution_clock::now();


    if (renderSettings.getRenderType() == RenderSettings::RenderType::RayTracing)
    {
        if (renderSettings.getThreadsCount() > 1)
        {
            threadPool.killAllTasks();
            threadPool.setWorkersCount(renderSettings.getThreadsCount());
            threadPool.beginTaskGroup();

            int x_side = 64, y_side = 64;
            for (int y = 0; y < renderTarget.height; y += y_side)
            {
                for (int x = 0; x < renderTarget.width; x += x_side)
                {
                    Core::RenderParams taskParams = params;
                    taskParams.viewport = Core::make_rect(x_side, y_side, x, y);
                    threadPool.addTask([taskParams]() { Core::renderScene(taskParams); });
                }
            }

            threadPool.endTaskGroup();
        }
    }
    else
    {
        Core::renderScene(params);
    }


    auto timeEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> durr = timeEnd - timeStart;

    std::stringstream buff;
    buff << "rendered in " << std::setprecision(3) << std::fixed << durr.count() << " ms. "
        << "(" << (int)(1000.0 / durr.count()) << " FPS).";
    std::string message = buff.str();
    getFactory().getInfoManager()->logInfo(message.c_str());
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
