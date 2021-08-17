#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include "Managers/IManager.hpp"
#include "RenderSettings/RenderSettings.hpp"


class SettingsManager : public IManager
{
public:
    explicit SettingsManager(IManagerFactory& managerFactory);
    virtual ~SettingsManager() = default;

    RenderSettings getRenderSettings();
    void updateRenderSettings(RenderSettings newSettings);

protected:
    virtual void onBeforeGetRenderSettings() {}
    virtual void onBeforeUpdateRenderSettings(RenderSettings newSettings) {}
    virtual void onUpdateRenderSettings();

private:
    RenderSettings renderSettings;
};

#endif // SETTINGSMANAGER_HPP
