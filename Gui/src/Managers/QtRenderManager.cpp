#include "QtRenderManager.hpp"


QtRenderManager::QtRenderManager(IManagerFactory &factory)
    : RenderManager(factory)
{
}

void QtRenderManager::onSceneRender(Scene &scene, Camera &camera)
{
    emit sceneRenderSignal(scene, camera);
}

RenderTarget QtRenderManager::getRenderTarget()
{
    return RenderTarget();
}
