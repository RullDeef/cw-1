#include "FreeFlyDispatcher.hpp"
#include "Managers/CameraManager.hpp"
#include <QKeyEvent>


FreeFlyDispatcher::FreeFlyDispatcher(IManagerFactory &managerFactory)
    : managerFactory(managerFactory)
{
}

void FreeFlyDispatcher::enable()
{
    enabled = true;
}

void FreeFlyDispatcher::disable()
{
    enabled = false;
}

void FreeFlyDispatcher::update()
{
    if (enabled)
        managerFactory.getCameraManager()->freeFlyCamera
            (flySpeed * forward, -flySpeed * right, flySpeed * up);
}

void FreeFlyDispatcher::keyPressed(int key)
{
    switch (key)
    {
        case Qt::Key_W: forward = -1; break;
        case Qt::Key_A: right = 1; break;
        case Qt::Key_S: forward = 1; break;
        case Qt::Key_D: right = -1; break;
        default: break;
    }
}

void FreeFlyDispatcher::keyReleased(int key)
{
    switch (key)
    {
        case Qt::Key_W: forward = 0; break;
        case Qt::Key_A: right = 0; break;
        case Qt::Key_S: forward = 0; break;
        case Qt::Key_D: right = 0; break;
        default: break;
    }
}

void FreeFlyDispatcher::mousePressed(double x, double y)
{
    dragging = true;
    x_prev = x;
    y_prev = y;
}

void FreeFlyDispatcher::mouseMoved(double x, double y)
{
    if (dragging)
    {
        double dx = x - x_prev;
        double dy = y - y_prev;
        x_prev = x;
        y_prev = y;
        managerFactory.getCameraManager()->rotateCamera(dragSpeed * dx, dragSpeed * dy);
    }
}

void FreeFlyDispatcher::mouseReleased()
{
    dragging = false;
}
