#ifndef INSPECTORFRAME_HPP
#define INSPECTORFRAME_HPP

#include <Managers/IManagerFactory.hpp>
#include "Frames/IFrame.hpp"


class InspectorFrame : public IFrame
{
public:
    explicit InspectorFrame(IManagerFactory& managerFactory, QWidget* parent = nullptr);

    void updateInspectee();

private:
    IManagerFactory* managerFactory;
};

#endif // INSPECTORFRAME_HPP
