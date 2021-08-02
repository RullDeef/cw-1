#include <QPaintEvent>
#include <QFileDialog>
#include <QPainter>
#include <QApplication>
#include "Managers/CameraManager.hpp"
#include "Managers/ObjectManager.hpp"
#include "Frames/ViewportFrame/ViewportFrame.hpp"
#include <QTimer>


ViewportFrame::ViewportFrame(IManagerFactory &managerFactory, QWidget *parent)
        : IFrame(u8"видовое окно", parent), managerFactory(&managerFactory), freeFlyDispatcher(managerFactory)
{
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    freeFlyTimer = new QTimer(this);
    connect(freeFlyTimer, &QTimer::timeout, this, &ViewportFrame::updateFreeFly);
    freeFlyTimer->start(1);

    freeFlyDispatcher.enable();
}

void ViewportFrame::paintEvent(QPaintEvent *event)
{
    {
        QPainter painter(this);
        redraw();
        painter.drawImage(0, 0, image);
    }

    ads::CDockWidget::paintEvent(event);
    update();
}

void ViewportFrame::resizeEvent(QResizeEvent *event)
{
    image = QImage(width(), height(), QImage::Format_ARGB32);
    redraw();
}

void ViewportFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        freeFlyDispatcher.mousePressed(event->x(), event->y());
    else
        managerFactory->getObjectManager()->toggleSelection(event->x(), event->y());

    QWidget::mousePressEvent(event);
}

void ViewportFrame::mouseMoveEvent(QMouseEvent *event)
{
    freeFlyDispatcher.mouseMoved(event->x(), event->y());

    QWidget::mouseMoveEvent(event);
    redraw();
    repaint();
}

void ViewportFrame::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers().testFlag(Qt::ShiftModifier))
    {
        // free camera fly
        freeFlyDispatcher.keyPressed(event->key());
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void ViewportFrame::keyReleaseEvent(QKeyEvent *event)
{
    freeFlyDispatcher.keyReleased(event->key());
    QWidget::keyReleaseEvent(event);
}


void ViewportFrame::redraw()
{
    Core::RenderTarget renderTarget{};
    renderTarget.width = image.width();
    renderTarget.height = image.height();
    renderTarget.data = (Core::Pixel *) image.bits();

    managerFactory->getRenderManager()->renderSceneFast(renderTarget);
}

void ViewportFrame::saveToImage()
{
    QString filename = QFileDialog::getSaveFileName(this, u8"Выберите файл", nullptr, nullptr, nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    image.save(filename);
}

void ViewportFrame::updateFreeFly()
{
    freeFlyDispatcher.update();
}
