#include <QPaintEvent>
#include <QPainter>
#include <utility>
#include "ViewportFrame.hpp"


ViewportFrame::ViewportFrame(std::shared_ptr<RenderManager> renderManager, QWidget* parent)
    : IFrame(u8"видовое окно", parent), renderManager(std::move(renderManager))
{
}

void ViewportFrame::paintEvent(QPaintEvent* event)
{
    {
        QPainter painter(this);

        redraw();
        painter.drawImage(0, 0, image);
    }

    QDockWidget::paintEvent(event);
    update();
}

void ViewportFrame::resizeEvent(QResizeEvent* event)
{
    image = QImage(width(), height(), QImage::Format_ARGB32);
}

void ViewportFrame::redraw()
{
    Core::RenderTarget renderTarget{};
    renderTarget.width = image.width();
    renderTarget.height = image.height();
    renderTarget.data = (Core::Pixel*)image.bits();

    renderManager->renderScene(renderTarget);
}
