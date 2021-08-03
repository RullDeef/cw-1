#include <Frames/InspectorFrame/InspectorWidget/InspectorWidget.hpp>
#include "InspectorFrame.hpp"


InspectorFrame::InspectorFrame(IManagerFactory &managerFactory, QWidget *parent)
    : IFrame("Inspector", parent), managerFactory(&managerFactory)
{
    setWidget(new InspectorWidget());
}
