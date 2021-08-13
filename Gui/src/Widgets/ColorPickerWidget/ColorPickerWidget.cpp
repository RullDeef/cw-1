#include <QPainter>
#include <QColorDialog>
#include "ColorPickerWidget.hpp"


ColorPickerWidget::ColorPickerWidget(QWidget *parent) : QWidget(parent), color(QColor::fromRgb(255, 255, 255))
{
}

void ColorPickerWidget::setColor(QColor newColor)
{
    color = newColor;
}

void ColorPickerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QColorDialog dialog;
    if (dialog.exec())
    {
        color = dialog.selectedColor();
        repaint();
        emit colorPicked(color);
    }
}

void ColorPickerWidget::paintEvent(QPaintEvent *event)
{
    QPainter(this).fillRect(0, 0, width(), height(), color);
    QWidget::paintEvent(event);
}
