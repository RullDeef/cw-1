#include "Managers/SettingsManager.hpp"


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
