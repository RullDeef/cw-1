#ifndef QTRENDERMANAGER_HPP
#define QTRENDERMANAGER_HPP

#include <QObject>
#include <Widgets/RenderWidget.hpp>
#include <Managers/RenderManager.hpp>


class QtRenderManager : public QObject, public RenderManager
{
    Q_OBJECT

public:
    explicit QtRenderManager(IManagerFactory& factory);

    QWidget* getViewWidget();

    Rect getActiveViewport() override;

signals:
    void sceneRenderSignal(Scene& scene, Camera& camera);

protected slots:
    void renderWidgetResized();

protected:
    RenderTarget getRenderTarget() override;

    void onSceneRender(Scene &scene, Camera &camera) override;

private:
    RenderWidget* viewWidget;
};

#endif // QTRENDERMANAGER_HPP
