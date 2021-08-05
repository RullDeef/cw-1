#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/RenderManager.hpp"
#include "Managers/LoadManager.hpp"
#include "Managers/CameraManager.hpp"
#include "Managers/SelectionManager.hpp"


std::shared_ptr<SceneManager> IManagerFactory::getSceneManager()
{
    if (!sceneManager)
        sceneManager = createSceneManager();
    return sceneManager;
}

std::shared_ptr<CameraManager> IManagerFactory::getCameraManager()
{
    if (!cameraManager)
        cameraManager = createCameraManager();
    return cameraManager;
}

std::shared_ptr<RenderManager> IManagerFactory::getRenderManager()
{
    if (!renderManager)
        renderManager = createRenderManager();
    return renderManager;
}

std::shared_ptr<LoadManager> IManagerFactory::getLoadManager()
{
    if (!loadManager)
        loadManager = createLoadManager();
    return loadManager;
}

std::shared_ptr<SelectionManager> IManagerFactory::getSelectionManager()
{
    if (!selectionManager)
        selectionManager = createSelectionManager();
    return selectionManager;
}
