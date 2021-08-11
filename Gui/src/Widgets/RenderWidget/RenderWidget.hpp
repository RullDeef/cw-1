#ifndef RENDERWIDGET_HPP
#define RENDERWIDGET_HPP

#include <QWidget>
#include <RenderTarget/RenderTarget.hpp>


class RenderWidget : public QWidget
{
    Q_OBJECT

public:
    RenderTarget getRenderTarget();

    [[nodiscard]] QImage getImage() const;

signals:
    void widgetResized(RenderWidget* widget);

protected slots:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    /// TODO: make event filters (exclude mouse-key events)

private:
    QImage sceneImage;
};

#endif // RENDERWIDGET_HPP
