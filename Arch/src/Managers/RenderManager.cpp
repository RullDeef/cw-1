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

void RenderManager::renderSceneFast(Core::RenderTarget &renderTarget)
{
    Core::Scene scene = requireScene();
    Core::Camera camera = requireCamera(renderTarget);

    Core::Rect viewport = Core::make_rect(renderTarget.width, renderTarget.height);

    Core::renderScene({
                              renderTarget, scene, camera,
                              Core::RenderParams::RenderType::FastRenderType,
                              viewport
                      });
}

void RenderManager::renderSceneFancy(Core::RenderTarget &renderTarget)
{
    Core::Scene scene = requireScene();
    Core::Camera camera = requireCamera(renderTarget);

    const int patchSize = 64;
    int rows = renderTarget.height / patchSize + (renderTarget.height % patchSize == 0 ? 0 : 1);
    int cols = renderTarget.width / patchSize + (renderTarget.width % patchSize == 0 ? 0 : 1);

    std::vector<std::future<Core::StatusCode>> tasks;
    tasks.reserve(rows * cols);

    Core::RenderParams params {
        renderTarget, scene, camera,
        Core::RenderParams::RenderType::FancyRenderType
    };

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            params.viewport = Core::make_rect(patchSize, patchSize, patchSize * col, patchSize * row);
            tasks.push_back(std::async(std::launch::async, Core::renderScene, params));
        }
    }

    for (auto& task : tasks)
        task.wait();
}

Core::Camera RenderManager::requireCamera(const Core::RenderTarget& renderTarget)
{
    Core::Rect viewport = Core::make_rect(renderTarget.width, renderTarget.height);
    return requireCamera(viewport);
}

Core::Camera RenderManager::requireCamera(const Core::Rect &viewport)
{
    Core::Camera camera = getFactory().getCameraManager()->getActiveCamera().getAdaptee();
    Core::update_viewport(camera, viewport);
    return camera;
}

Core::Scene RenderManager::requireScene()
{
    Core::Scene scene = getFactory().getSceneManager()->getActiveScene()->getRawScene();
    return scene;
}
