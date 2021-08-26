#include "Managers/QtManagerFactory.hpp"
#include "Managers/QtSceneManager.hpp"
#include "Managers/QtCameraManager.hpp"
#include "Managers/QtRenderManager.hpp"
#include "Managers/QtLoadManager.hpp"
#include "Managers/QtSelectionManager.hpp"
#include "Managers/QtSettingsManager.hpp"
#include "Managers/QtInfoManager.hpp"


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

std::shared_ptr<SettingsManager> QtManagerFactory::getSettingsManager()
{
    if (!settingsManager)
        settingsManager = std::shared_ptr<SettingsManager>(new QtSettingsManager(*this));
    return settingsManager;
}

std::shared_ptr<InfoManager> QtManagerFactory::getInfoManager()
{
    if (!infoManager)
        infoManager = std::shared_ptr<InfoManager>(new QtInfoManager(*this));
    return infoManager;
}
