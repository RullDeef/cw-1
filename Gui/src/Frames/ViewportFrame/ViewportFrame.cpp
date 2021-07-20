#include <QPaintEvent>
#include <QPainter>
#include "ViewportFrame.hpp"


ViewportFrame::ViewportFrame(std::shared_ptr<RenderManager> renderManager, QWidget* parent)
    : IFrame(u8"Видовое окно", parent), renderManager(renderManager)
{
}

void ViewportFrame::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    redraw();
    painter.drawImage(0, 0, image);

    IFrame::paintEvent(event);

    update();
}

void ViewportFrame::resizeEvent(QResizeEvent* event)
{
    image = QImage(width(), height(), QImage::Format_ARGB32);
}

void ViewportFrame::redraw()
{
    Core::RenderTarget renderTarget;
    renderTarget.width = image.width();
    renderTarget.height = image.height();
    renderTarget.data = (Core::Pixel*)image.bits();

    renderManager->renderScene(renderTarget);
}
