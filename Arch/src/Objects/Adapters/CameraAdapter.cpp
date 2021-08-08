#include <Core/math/Sphere.hpp>
#include "Objects/Adapters/CameraAdapter.hpp"


ObjectAdapter<Camera>::ObjectAdapter(size_t id, Camera camera)
        : IObject(id), camera(camera)
{
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

    return ray.intersectsSphere(t, center, radius);
}
