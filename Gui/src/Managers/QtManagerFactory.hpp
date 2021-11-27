#ifndef QTMANAGERFACTORY_HPP
#define QTMANAGERFACTORY_HPP

#include "Managers/IManagerFactory.hpp"


class QtManagerFactory : public IManagerFactory
{
protected:
    std::shared_ptr<SceneManager> getSceneManager() override;
    std::shared_ptr<CameraManager> getCameraManager() override;
    std::shared_ptr<RenderManager> getRenderManager() override;
    std::shared_ptr<PortManager> getPortManager() override;
    std::shared_ptr<SelectionManager> getSelectionManager() override;
    std::shared_ptr<SettingsManager> getSettingsManager() override;
    std::shared_ptr<InfoManager> getInfoManager() override;

private:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<CameraManager> cameraManager;
    std::shared_ptr<RenderManager> renderManager;
    std::shared_ptr<PortManager> portManager;
    std::shared_ptr<SelectionManager> selectionManager;
    std::shared_ptr<SettingsManager> settingsManager;
    std::shared_ptr<InfoManager> infoManager;
};

#endif // QTMANAGERFACTORY_HPP
