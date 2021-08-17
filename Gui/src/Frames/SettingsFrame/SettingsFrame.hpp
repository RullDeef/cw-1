#ifndef SETTINGSFRAME_HPP
#define SETTINGSFRAME_HPP

#include <RenderSettings/RenderSettings.hpp>
#include <Managers/IManagerFactory.hpp>
#include "Frames/IFrame.hpp"


class SettingsFrame : public IFrame
{
public:
    explicit SettingsFrame(IManagerFactory& managerFactory, QWidget* parent);

protected slots:
    void renderSettingsChanged(RenderSettings newSettings);

private:
    IManagerFactory* managerFactory;
};

#endif // SETTINGSFRAME_HPP
