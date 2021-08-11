#ifndef RENDERWIDGET_HPP
#define RENDERWIDGET_HPP

#include <QWidget>
#include <RenderTarget/RenderTarget.hpp>


class RenderWidget : public QWidget
{
    Q_OBJECT

public:
    RenderTarget getSceneRenderTarget();
    RenderTarget getOverlayTarget();

    [[nodiscard]] QImage getImage() const;
    [[nodiscard]] QImage getOverlay() const;

signals:
    void widgetResized(RenderWidget* widget);

protected slots:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    /// TODO: make event filters (exclude mouse-key events)

private:
    void drawLayers();
    static RenderTarget createRenderTarget(QImage& source);

    QImage sceneImage;
    QImage overlayImage;
};

#endif // RENDERWIDGET_HPP
