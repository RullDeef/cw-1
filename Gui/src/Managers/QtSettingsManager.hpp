#ifndef QTSETTINGSMANAGER_HPP
#define QTSETTINGSMANAGER_HPP

#include <Managers/SettingsManager.hpp>
#include <QObject>


class QtSettingsManager : public QObject, public SettingsManager
{
    Q_OBJECT

public:
    explicit QtSettingsManager(IManagerFactory& factory);

signals:
    void beforeGetRendererSettingsSignal();
    void beforeUpdateRenderSettingsSignal(RenderSettings newSettings);
    void updateRenderSettingsSignal();

protected:
    void onBeforeGetRenderSettings() override;
    void onBeforeUpdateRenderSettings(RenderSettings newSettings) override;
    void onUpdateRenderSettings() override;
};

#endif // QTSETTINGSMANAGER_HPP
