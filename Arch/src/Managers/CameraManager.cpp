#include "Managers/CameraManager.hpp"


CameraManager::CameraManager(IManagerFactory &factory)
    : IManager(factory), mainCamera(-1, Core::make_camera(), AdapterPolicy::WeakOwnership)
{
    mainCamera.getAdaptee().
     //   model_mat = Core::make_mat_translation(0, 0, -300);
      model_mat = Core::make_mat_translation(Core::make_pos(50, -100, -400));
}

ObjectAdapter<Core::Camera> &CameraManager::getActiveCamera()
{
    return mainCamera;
}

const ObjectAdapter<Core::Camera> &CameraManager::getActiveCamera() const
{
    return mainCamera;
}

void CameraManager::dragCamera(double dx, double dy)
{
    Core::Camera& cam = getActiveCamera().getAdaptee();
    Core::Mat transform = Core::make_mat_translation(dx, dy, 0);

    cam.model_mat = transform * cam.model_mat;
}

void CameraManager::rotateCamera(double dx, double dy)
{
//    vec x_loc = vec_create(1, 0, 0);
//    x_loc = tf_apply_inverse(view.model_tf, x_loc);
//    tf_rotate(view.model_tf, x_loc, -dy);
//
//    vec y_loc = vec_create(0, 1, 0);
//    y_loc = tf_apply_inverse(view.model_tf, y_loc);
//    tf_rotate(view.model_tf, y_loc, -dx);

    Core::Camera& cam = getActiveCamera().getAdaptee();

    Core::Vec x_loc = Core::make_dir(1, 0, 0);
    x_loc = inverse(cam.model_mat) * x_loc;

    Core::Vec y_loc = Core::make_dir(0, 1, 0);
    y_loc = inverse(cam.model_mat) * y_loc;

    Core::Mat transform =
            Core::make_mat_rotation(x_loc, -dy)
            * Core::make_mat_rotation(y_loc, dx);

    cam.model_mat = transform * cam.model_mat;
}

void CameraManager::zoomCamera(double factor)
{

}

void CameraManager::freeFlyCamera(double forward, double right, double up)
{
    Core::Camera& cam = getActiveCamera().getAdaptee();

    Core::Vec offset = Core::make_dir(right, up, forward);
    Core::Mat transform = Core::make_mat_translation(offset);

    cam.model_mat = transform * cam.model_mat;
}
