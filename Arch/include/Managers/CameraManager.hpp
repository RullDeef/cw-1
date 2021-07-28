#ifndef CAMERAMANAGER_HPP
#define CAMERAMANAGER_HPP

#include "Core/Objects/Camera.hpp"
#include "Objects/ObjectAdapter.hpp"
#include "Scene/Scene.hpp"
#include "Managers/IManager.hpp"


class CameraManager : public IManager
{
public:
    explicit CameraManager(IManagerFactory& factory);

    ObjectAdapter<Core::Camera>& getActiveCamera();
    const ObjectAdapter<Core::Camera>& getActiveCamera() const;

    /// делать функции перемещения вида здесь?
    /// или где.? в гуи? ну это по большей части относится именно к окошку с видом.
    /// там можно будет мышкой перетаскивать и поворачивать активную камеру. ХЫЫЫММММ... может.
    /// Ну вообще... А почему в гуи? Но камера же как обычные модельки рассматривается? И не одна же камера может быть
    /// аыаыаыаыаыаыаыаыаыа. Время то есть, можно делать красиво :3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 *лизь* UwU
    /// Ну вопрос из разряда сделать всё красиво или сделать всё быстро. Дя :3 <3 <3 <3<3 <3 <3<3 <3 <3<3 <3 <3<3 <3 <3<3 <3 <3  *цмок*

    /// сделаем здесь. Иначе смысла в этом классе больше нет. угу

    // translates camera along view plane
    void dragCamera(double dx, double dy);

    // rotates camera around itself (or around selected object?)
    void rotateCamera(double dx, double dy);

    // zoomIn & zoomOut (wheel up/down)
    void zoomCamera(double factor);

    void freeFlyCamera(double forward, double right, double up);

private:
    Scene::iterator cameraIterator;
    ObjectAdapter<Core::Camera> mainCamera;
};

#endif // CAMERAMANAGER_HPP
