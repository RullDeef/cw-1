#include <QPainter>
#include "RenderWidget.hpp"


RenderTarget RenderWidget::getRenderTarget()
{
    unsigned char* data = sceneImage.bits();
    int width = sceneImage.width();
    int height = sceneImage.height();

    return RenderTarget(data, width, height);
}

QImage RenderWidget::getImage() const
{
    return sceneImage;
}

void RenderWidget::paintEvent(QPaintEvent *event)
{
    {
        QPainter painter(this);
        painter.drawImage(0, 0, sceneImage);
    }

    QWidget::paintEvent(event);
}

void RenderWidget::resizeEvent(QResizeEvent *event)
{
    sceneImage = QImage(width(), height(), QImage::Format_ARGB32);
    QWidget::resizeEvent(event);

    emit widgetResized(this);
}
