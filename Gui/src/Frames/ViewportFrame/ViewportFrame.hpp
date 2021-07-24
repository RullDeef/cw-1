#ifndef VIEWPORTFRAME_HPP
#define VIEWPORTFRAME_HPP

#include <memory>
#include <QImage>
#include <IManagerFactory.hpp>
#include "IFrame.hpp"
#include "RenderManager.hpp"

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;


class ViewportFrame : public IFrame
{
    Q_OBJECT

public:
    ViewportFrame(IManagerFactory& managerFactory, QWidget* parent = nullptr);
    virtual ~ViewportFrame() = default;

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

    enum class ControllState
    {
        DragState,
        RotateState
    };

    ControllState state;
};

#endif // VIEWPORTFRAME_HPP
