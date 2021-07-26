#include <utility>
#include <QPaintEvent>
#include <QFileDialog>
#include <QPainter>
#include <QApplication>
#include "Managers/CameraManager.hpp"
#include "Frames/ViewportFrame/ViewportFrame.hpp"


ViewportFrame::ViewportFrame(IManagerFactory &managerFactory, QWidget *parent)
        : IFrame(u8"видовое окно", parent), managerFactory(&managerFactory)
{
}

void ViewportFrame::paintEvent(QPaintEvent *event)
{
    {
        QPainter painter(this);

        redraw();
        painter.drawImage(0, 0, image);
    }

    ads::CDockWidget::paintEvent(event);
    //update();
}

void ViewportFrame::resizeEvent(QResizeEvent *event)
{
    image = QImage(width(), height(), QImage::Format_ARGB32);
}

void ViewportFrame::mousePressEvent(QMouseEvent *event)
{
    x_prev = event->x();
    y_prev = event->y();

    if (QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
        state = ControlState::RotateState;
    else
        state = ControlState::DragState;

    QWidget::mousePressEvent(event);
}

void ViewportFrame::mouseMoveEvent(QMouseEvent *event)
{
    double dx = event->x() - x_prev;
    double dy = event->y() - y_prev;

    x_prev = event->x();
    y_prev = event->y();

    if (state == ControlState::DragState)
    {
        double scale = 0.25;
        managerFactory->getCameraManager()->dragCamera(scale * dx, -scale * dy);
    }
    else if (state == ControlState::RotateState)
    {
        double scale = 0.0025;
        managerFactory->getCameraManager()->rotateCamera(-scale * dx, -scale * dy);
    }

    QWidget::mouseMoveEvent(event);
    repaint();
}

void ViewportFrame::redraw()
{
    Core::RenderTarget renderTarget{};
    renderTarget.width = image.width();
    renderTarget.height = image.height();
    renderTarget.data = (Core::Pixel *) image.bits();

    managerFactory->getRenderManager()->renderScene(renderTarget);
}

void ViewportFrame::saveToImage()
{
    QString filename = QFileDialog::getSaveFileName(this, u8"Выберите файл", nullptr, nullptr, nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    image.save(filename);
}
