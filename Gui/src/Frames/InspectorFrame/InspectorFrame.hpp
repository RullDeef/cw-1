#ifndef INSPECTORFRAME_HPP
#define INSPECTORFRAME_HPP

#include <Managers/IManagerFactory.hpp>
#include "Frames/InspectorFrame/InspectorWidget/InspectorWidget.hpp"
#include "Frames/IFrame.hpp"


class InspectorFrame : public IFrame
{
    Q_OBJECT

public:
    explicit InspectorFrame(IManagerFactory& managerFactory, QWidget* parent = nullptr);

protected slots:
    void updateInspectee();

    void objectChanged();

private:
    IManagerFactory* managerFactory;
    InspectorWidget* inspectorWidget;
};

#endif // INSPECTORFRAME_HPP
