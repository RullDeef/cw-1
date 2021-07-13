#include <QPaintEvent>
#include <QPainter>
#include "ViewportFrame.hpp"


ViewportFrame::ViewportFrame(QWidget* parent)
    : IFrame(u8"Видовое окно", parent)
{
}

void ViewportFrame::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.drawLine(0, 0, width(), height());
    painter.drawLine(0, height(), width(), 0);

    IFrame::paintEvent(event);
}
