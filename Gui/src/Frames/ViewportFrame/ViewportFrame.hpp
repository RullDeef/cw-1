#ifndef VIEWPORTFRAME_HPP
#define VIEWPORTFRAME_HPP

#include <memory>
#include <QImage>
#include <Managers/IManagerFactory.hpp>
#include <Managers/RenderManager.hpp>
#include "Frames/IFrame.hpp"

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;


class ViewportFrame : public IFrame
{
    Q_OBJECT

public:
    explicit ViewportFrame(IManagerFactory& managerFactory, QWidget* parent = nullptr);
    virtual ~ViewportFrame() = default;

    void saveToImage();

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
    void redraw();

    QImage image;
    IManagerFactory* managerFactory;

    double x_prev;
    double y_prev;

    enum class ControlState
    {
        DragState,
        RotateState
    };

    ControlState state;
};

#endif // VIEWPORTFRAME_HPP
