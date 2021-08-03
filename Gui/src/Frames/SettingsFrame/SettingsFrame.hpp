#ifndef SETTINGSFRAME_HPP
#define SETTINGSFRAME_HPP

#include <Managers/IManagerFactory.hpp>
#include "Frames/IFrame.hpp"


class SettingsFrame : public IFrame
{
public:
    explicit SettingsFrame(IManagerFactory& managerFactory, QWidget* parent);

private:
    IManagerFactory* managerFactory;
};

#endif // SETTINGSFRAME_HPP
