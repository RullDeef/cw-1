#ifndef QTCAMERAMANAGER_HPP
#define QTCAMERAMANAGER_HPP

#include <QObject>
#include <Managers/CameraManager.hpp>


class QtCameraManager : public QObject, public CameraManager
{
    Q_OBJECT

public:
    explicit QtCameraManager(IManagerFactory& factory);

signals:
    void activeCameraSwitchSignal(std::shared_ptr<IObject> activeCamera);
    void cameraChangeSignal(std::shared_ptr<IObject> camera);

protected:
    void onActiveCameraSwitch(std::shared_ptr<IObject> activeCamera) override;
    void onCameraChange(std::shared_ptr<IObject> camera) override;
};

#endif // QTCAMERAMANAGER_HPP
