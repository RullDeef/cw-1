#include "Managers/SettingsManager.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/RenderManager.hpp"


SettingsManager::SettingsManager(IManagerFactory &managerFactory)
    : IManager(managerFactory)
{
}

RenderSettings SettingsManager::getRenderSettings()
{
    onBeforeGetRenderSettings();
    return renderSettings;
}

void SettingsManager::updateRenderSettings(RenderSettings newSettings)
{
    onBeforeUpdateRenderSettings(newSettings);
    renderSettings = newSettings;
    onUpdateRenderSettings();
}

void SettingsManager::onUpdateRenderSettings()
{
    getFactory().getRenderManager()->renderActiveScene();
}
