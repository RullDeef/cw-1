#include "Frames/SettingsFrame/SettingsWidget/SettingsWidget.hpp"
#include "SettingsFrame.hpp"


SettingsFrame::SettingsFrame(IManagerFactory &managerFactory, QWidget *parent)
    : IFrame("Settings", parent), managerFactory(&managerFactory)
{
    setWidget(new SettingsWidget());
}
