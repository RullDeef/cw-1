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
    void activeCameraSwitchSignal(Camera& activeCamera);
    void cameraChangeSignal(Camera& camera);

protected:
    void onActiveCameraSwitch(Camera& activeCamera) override;
    void onCameraChange(Camera& camera) override;
};

#endif // QTCAMERAMANAGER_HPP
