#ifndef QTRENDERMANAGER_HPP
#define QTRENDERMANAGER_HPP

#include <QObject>
#include <Widgets/RenderWidget/RenderWidget.hpp>
#include <Managers/RenderManager.hpp>


class QtRenderManager : public QObject, public RenderManager
{
    Q_OBJECT

public:
    explicit QtRenderManager(IManagerFactory& factory);

    QWidget* getViewWidget();

    Rect getActiveViewport() override;

signals:
    void sceneRenderSignal(Scene &scene, Camera &camera, const RenderSettings &renderSettings);

protected slots:
    void renderWidgetResized();

protected:
    RenderTarget getSceneRenderTarget() override;
    RenderTarget getOverlayRenderTarget() override;

    void onSceneRender(Scene &scene, Camera &camera, const RenderSettings &renderSettings) override;

private:
    void paintOverlay();

    RenderWidget* viewWidget;
};

#endif // QTRENDERMANAGER_HPP
