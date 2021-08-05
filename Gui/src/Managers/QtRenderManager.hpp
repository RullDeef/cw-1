#ifndef QTRENDERMANAGER_HPP
#define QTRENDERMANAGER_HPP

#include <QObject>
#include <Managers/RenderManager.hpp>


class QtRenderManager : public QObject, public RenderManager
{
    Q_OBJECT

public:
    explicit QtRenderManager(IManagerFactory& factory);

signals:
    void sceneRenderSignal(Scene& scene, Camera& camera);

protected:
    RenderTarget getRenderTarget() override;

    void onSceneRender(Scene &scene, Camera &camera) override;
};

#endif // QTRENDERMANAGER_HPP
