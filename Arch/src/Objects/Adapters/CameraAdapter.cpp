#include <Core/common/math/Sphere.hpp>
#include "Core/common/math/Ray.hpp"
#include "Objects/Adapters/CameraAdapter.hpp"


ObjectAdapter<Core::Camera>::ObjectAdapter(size_t id, Core::Camera camera, AdapterPolicy policy)
        : IObject(id), camera(camera), policy(policy)
{
}

Core::Camera& ObjectAdapter<Core::Camera>::getAdaptee()
{
    return camera;
}

const Core::Camera& ObjectAdapter<Core::Camera>::getAdaptee() const
{
    return camera;
}

void ObjectAdapter<Core::Camera>::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}

bool ObjectAdapter<Core::Camera>::intersects(double &t, const Core::Ray &ray)
{
    const double radius = 1.0; /// TODO: magic constant
    Core::Sphere sphere = Core::make_sphere(camera.eye, radius);

    return Core::ray_intersects(t, ray, sphere);
}

