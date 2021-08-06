#include <QWidget>
#include "QtRenderManager.hpp"


QtRenderManager::QtRenderManager(IManagerFactory &factory)
    : RenderManager(factory), viewWidget(new RenderWidget())
{
    connect(viewWidget, &RenderWidget::widgetResized, this, &QtRenderManager::renderWidgetResized);
}

QWidget *QtRenderManager::getViewWidget()
{
    return viewWidget;
}

Rect QtRenderManager::getActiveViewport()
{
    int width = viewWidget->width();
    int height = viewWidget->height();

    return Rect(0, 0, width, height);
}

void QtRenderManager::onSceneRender(Scene &scene, Camera &camera)
{
    RenderManager::onSceneRender(scene, camera);

    viewWidget->repaint();

    emit sceneRenderSignal(scene, camera);
}

RenderTarget QtRenderManager::getRenderTarget()
{
    return viewWidget->getRenderTarget();
}

void QtRenderManager::renderWidgetResized()
{
    renderActiveScene();
}
