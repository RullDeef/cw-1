#include "IFrame.hpp"


IFrame::IFrame(const QString& title, QWidget* parent)
    : QDockWidget(parent)
{
    setWindowTitle(title);
    setAllowedAreas(Qt::AllDockWidgetAreas);
}
