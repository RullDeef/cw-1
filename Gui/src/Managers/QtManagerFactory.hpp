#ifndef QTMANAGERFACTORY_HPP
#define QTMANAGERFACTORY_HPP

#include <QWidget>
#include "Managers/IManagerFactory.hpp"


class QtManagerFactory : public IManagerFactory
{
protected:
    std::shared_ptr<SceneManager> getSceneManager() override;
    std::shared_ptr<CameraManager> getCameraManager() override;
    std::shared_ptr<RenderManager> getRenderManager() override;
    std::shared_ptr<LoadManager> getLoadManager() override;
    std::shared_ptr<SelectionManager> getSelectionManager() override;

private:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<CameraManager> cameraManager;
    std::shared_ptr<RenderManager> renderManager;
    std::shared_ptr<LoadManager> loadManager;
    std::shared_ptr<SelectionManager> selectionManager;

    QWidget* mainWindow;
};

#endif // QTMANAGERFACTORY_HPP
