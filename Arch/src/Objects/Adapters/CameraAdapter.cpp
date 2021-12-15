#include <Core/math/Sphere.hpp>
#include "Objects/Adapters/CameraAdapter.hpp"


ObjectAdapter<Camera>::ObjectAdapter(size_t id, Camera camera)
        : IObject(id), camera(camera)
{
    setPosition(camera.getPosition());
    setRotation(Vector(camera.getPitch(), camera.getYaw(), 0, 0) * 180.0 / M_PI);
}

Camera& ObjectAdapter<Camera>::getAdaptee()
{
    return camera;
}

const Camera& ObjectAdapter<Camera>::getAdaptee() const
{
    return camera;
}

void ObjectAdapter<Camera>::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}

bool ObjectAdapter<Camera>::intersects(double &t, const Ray &ray)
{
    constexpr auto radius = 1.0;
    auto center = camera.getPosition();

    if ((ray.getPosition() - center).is_zero())
        return false;

    return ray.intersectsSphere(t, center, radius);
}

void ObjectAdapter<Camera>::onTransformChange()
{
    IObject::onTransformChange();

    double pitch = getRotation().getX() / 180 * M_PI;
    double yaw = getRotation().getY() / 180 * M_PI;

    camera.setPosition(getPosition());
    camera.setPitch(pitch);
    camera.setYaw(yaw);
}
