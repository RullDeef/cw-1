#include "Objects/Adapters/LightAdapter.hpp"


ObjectAdapter<Light>::ObjectAdapter(size_t id, Light light)
    : IObject(id), light(light)
{
}

Light& ObjectAdapter<Light>::getAdaptee()
{
    return light;
}

const Light& ObjectAdapter<Light>::getAdaptee() const
{
    return light;
}

void ObjectAdapter<Light>::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}

bool ObjectAdapter<Light>::intersects(double& t, const Ray& ray)
{
    const Camera& camera = *(ray.getCamera());

    Vector center = camera.project(light.getPosition(), ray.getViewport());
    Vector ray_pos = camera.project(ray.getPosition() + ray.getDirection(), ray.getViewport());
    Vector delta = center - ray_pos;

    const double radius = 10.0;

    if (delta.getX() * delta.getX() + delta.getY() * delta.getY() <= radius * radius)
        return ray.intersectsPlane(t, light.getPosition(), -ray.getDirection());
    return false;
}

void ObjectAdapter<Light>::onTransformChange()
{
    IObject::onTransformChange();

    light.setPosition(getPosition());
    light.setDirection(Matrix::rotate(getRotation() * M_PI / 180.0) * Vector(1, 0, 0, 0));
}
