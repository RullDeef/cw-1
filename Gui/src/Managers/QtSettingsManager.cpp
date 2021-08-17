#include "QtSettingsManager.hpp"


QtSettingsManager::QtSettingsManager(IManagerFactory &factory)
    : SettingsManager(factory)
{
}

void QtSettingsManager::onBeforeGetRenderSettings()
{
    SettingsManager::onBeforeGetRenderSettings();

    emit beforeGetRendererSettingsSignal();
}

void QtSettingsManager::onBeforeUpdateRenderSettings(RenderSettings newSettings)
{
    SettingsManager::onBeforeUpdateRenderSettings(newSettings);

    emit beforeUpdateRenderSettingsSignal(newSettings);
}

void QtSettingsManager::onUpdateRenderSettings()
{
    SettingsManager::onUpdateRenderSettings();

    emit updateRenderSettingsSignal();
}
