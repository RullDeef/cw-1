#include "Managers/QtManagerFactory.hpp"
#include "Managers/QtSceneManager.hpp"
#include "Managers/QtCameraManager.hpp"
#include "Managers/QtRenderManager.hpp"
#include "Managers/QtLoadManager.hpp"
#include "Managers/QtSelectionManager.hpp"


QtManagerFactory::QtManagerFactory()
{
}

std::shared_ptr<SceneManager> QtManagerFactory::getSceneManager()
{
    if (!sceneManager)
        sceneManager = std::shared_ptr<SceneManager>(new QtSceneManager(*this));
    return sceneManager;
}

std::shared_ptr<CameraManager> QtManagerFactory::getCameraManager()
{
    if (!cameraManager)
        cameraManager = std::shared_ptr<CameraManager>(new QtCameraManager(*this));
    return cameraManager;
}

std::shared_ptr<RenderManager> QtManagerFactory::getRenderManager()
{
    if (!renderManager)
        renderManager = std::shared_ptr<RenderManager>(new QtRenderManager(*this));
    return renderManager;
}

std::shared_ptr<LoadManager> QtManagerFactory::getLoadManager()
{
    if (!loadManager)
        loadManager = std::shared_ptr<LoadManager>(new QtLoadManager(*this));
    return loadManager;
}

std::shared_ptr<SelectionManager> QtManagerFactory::getSelectionManager()
{
    if (!selectionManager)
        selectionManager = std::shared_ptr<SelectionManager>(new QtSelectionManager(*this));
    return selectionManager;
}
