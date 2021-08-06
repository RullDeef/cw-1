#include <Core/common/math/Sphere.hpp>
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
    return false;
//    const double radius = 1.0; /// TODO: move this into Camera class
//    Core::Sphere sphere = Core::make_sphere(camera.eye, radius);
//
//    return Core::ray_intersects(t, ray, sphere);
}

