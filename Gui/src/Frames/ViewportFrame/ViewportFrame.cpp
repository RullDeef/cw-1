#include <QPaintEvent>
#include <QFileDialog>
#include <QPainter>
#include <QLayout>
#include <QApplication>
#include "Managers/CameraManager.hpp"
#include "Managers/SelectionManager.hpp"
#include "Frames/ViewportFrame/ViewportFrame.hpp"
#include <QTimer>
#include <Managers/QtRenderManager.hpp>


ViewportFrame::ViewportFrame(IManagerFactory &managerFactory, QWidget *parent)
        : IFrame(u8"видовое окно", parent), managerFactory(&managerFactory), freeFlyDispatcher(managerFactory)
{
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    auto renderManager = dynamic_cast<QtRenderManager*>(managerFactory.getRenderManager().get());
    // setLayout(new QVBoxLayout());
    setWidget(renderManager->getViewWidget());

    freeFlyTimer = new QTimer(this);
    connect(freeFlyTimer, &QTimer::timeout, this, &ViewportFrame::updateFreeFly);
    freeFlyTimer->start(1);

    freeFlyDispatcher.enable();

    // setMouseTracking(true);
}

void ViewportFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        freeFlyDispatcher.mousePressed(event->x(), event->y());
    else
        managerFactory->getSelectionManager()->toggleSelection(event->x(), event->y());

    QWidget::mousePressEvent(event);
}

void ViewportFrame::mouseMoveEvent(QMouseEvent *event)
{
    freeFlyDispatcher.mouseMoved(event->x(), event->y());

    QWidget::mouseMoveEvent(event);
    managerFactory->getRenderManager()->renderActiveScene();
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

void ViewportFrame::saveToImage()
{
    QString filename = QFileDialog::getSaveFileName(this, u8"Выберите файл", nullptr, nullptr, nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    dynamic_cast<RenderWidget*>(widget())->getImage().save(filename);
}

void ViewportFrame::updateFreeFly()
{
    if (freeFlyDispatcher.update())
        managerFactory->getRenderManager()->renderActiveScene();
}
