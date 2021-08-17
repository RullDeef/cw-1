#include <Managers/SettingsManager.hpp>
#include "Frames/SettingsFrame/SettingsFrame.hpp"
#include "Frames/SettingsFrame/SettingsWidget/SettingsWidget.hpp"


SettingsFrame::SettingsFrame(IManagerFactory &managerFactory, QWidget *parent)
    : IFrame("Settings", parent), managerFactory(&managerFactory)
{
    auto settingsWidget = new SettingsWidget();
    setWidget(settingsWidget);

    settingsWidget->setRenderSettings(managerFactory.getSettingsManager()->getRenderSettings());

    connect(settingsWidget, &SettingsWidget::renderSettingsChangedSignal, this, &SettingsFrame::renderSettingsChanged);
}

void SettingsFrame::renderSettingsChanged(RenderSettings newSettings)
{
    managerFactory->getSettingsManager()->updateRenderSettings(newSettings);
}
