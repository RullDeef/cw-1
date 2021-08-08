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
    try
    {
        Scene& scene = getFactory().getSceneManager()->getActiveScene();
        auto camera = getFactory().getCameraManager()->getActiveCamera();

        onBeforeSceneRender(scene, camera);
        renderScene(scene, camera);
        onSceneRender(scene, camera);
    }
    catch (...)
    {
    }
}

void RenderManager::renderScene(Scene &scene, Camera &camera)
{
    Core::Scene rawScene = scene.getRawScene();
    Core::RenderParams params = Core::make_render_params(getRenderTarget(), rawScene, camera);
    Core::renderScene(params);
    Core::destroy(rawScene);
}

void RenderManager::onBeforeSceneRender(Scene &scene, Camera &camera)
{
}

void RenderManager::onSceneRender(Scene &scene, Camera &camera)
{
}
