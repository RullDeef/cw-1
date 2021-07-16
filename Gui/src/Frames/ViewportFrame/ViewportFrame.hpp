#ifndef VIEWPORTFRAME_HPP
#define VIEWPORTFRAME_HPP

#include <memory>
#include <QImage>
#include "IFrame.hpp"
#include "RenderManager.hpp"

class QPaintEvent;
class QResizeEvent;


class ViewportFrame : public IFrame
{
    Q_OBJECT

public:
    ViewportFrame(std::shared_ptr<RenderManager> renderManager, QWidget* parent = nullptr);
    virtual ~ViewportFrame() = default;

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    void redraw();

    QImage image;
    std::shared_ptr<RenderManager> renderManager;
};

#endif // VIEWPORTFRAME_HPP
