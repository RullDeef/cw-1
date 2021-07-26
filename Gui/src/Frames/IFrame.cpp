#include "Frames/IFrame.hpp"


IFrame::IFrame(const QString& title, QWidget* parent)
    : ads::CDockWidget(title, parent)
{
    setWindowTitle(title);
    // setAllowedAreas(Qt::AllDockWidgetAreas);
}
