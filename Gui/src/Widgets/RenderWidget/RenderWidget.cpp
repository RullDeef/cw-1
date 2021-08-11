#include <QPainter>
#include "RenderWidget.hpp"


RenderTarget RenderWidget::getSceneRenderTarget()
{
    return createRenderTarget(sceneImage);
}

RenderTarget RenderWidget::getOverlayTarget()
{
    return createRenderTarget(overlayImage);
}

QImage RenderWidget::getImage() const
{
    return sceneImage;
}

QImage RenderWidget::getOverlay() const
{
    return overlayImage;
}

void RenderWidget::paintEvent(QPaintEvent *event)
{
    drawLayers();
    QWidget::paintEvent(event);
}

void RenderWidget::resizeEvent(QResizeEvent *event)
{
    sceneImage = QImage(width(), height(), QImage::Format_ARGB32);
    overlayImage = QImage(width(), height(), QImage::Format_ARGB32);
    QWidget::resizeEvent(event);

    emit widgetResized(this);
}

void RenderWidget::drawLayers()
{
    QPainter painter(this);
    painter.drawImage(0, 0, sceneImage);
    painter.drawImage(0, 0, overlayImage);
}

RenderTarget RenderWidget::createRenderTarget(QImage& source)
{
    unsigned char* data = source.bits();
    int width = source.width();
    int height = source.height();

    return RenderTarget(data, width, height);
}
