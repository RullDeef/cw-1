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
    constexpr auto radius = 1.0;
    auto center = light.getPosition();

    return ray.intersectsSphere(t, center, radius);
}

void ObjectAdapter<Light>::onTransformChange()
{
    IObject::onTransformChange();

    light.setPosition(getPosition());
    light.setDirection(Matrix::rotate(getRotation()) * Vector(1, 0, 0));
}
