#ifndef VIEWPORTFRAME_HPP
#define VIEWPORTFRAME_HPP

#include <memory>
#include <QImage>
#include <Managers/IManagerFactory.hpp>
#include <Managers/RenderManager.hpp>
#include <QTimer>
#include "Frames/IFrame.hpp"
#include "Frames/ViewportFrame/FreeFlyDispatcher/FreeFlyDispatcher.hpp"

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
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

protected slots:
    void updateFreeFly();

private:
    void redraw();

    IManagerFactory* managerFactory;

    FreeFlyDispatcher freeFlyDispatcher;
    QTimer* freeFlyTimer;
};

#endif // VIEWPORTFRAME_HPP
