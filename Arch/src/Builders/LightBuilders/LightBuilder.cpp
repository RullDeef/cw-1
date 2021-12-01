#include "Builders/DefaultIDGenerator.hpp"
#include "Builders/LightBuilders/LightBuilder.hpp"
#include "Objects/Adapters/LightAdapter.hpp"


LightBuilder& LightBuilder::setIntensity(double newIntensity)
{
    if (newIntensity < 0.0 || 1.0 < newIntensity)
        throw std::runtime_error("bad light intensity");

    intensity = newIntensity;
    return *this;
}

LightBuilder& LightBuilder::setDirection(const Vector& newDirection)
{
    if (newDirection.is_zero())
        throw std::runtime_error("bad light direction");

    if (newDirection.getY() == 0.0 && newDirection.getZ() == 0.0)
    {
        if (newDirection.getX() > 0.0)
            rotation = Vector(0, 0, 0, 0);
        else
            rotation = Vector(0, 180, 0, 0);
    }
    else
    {
        Vector dirX = newDirection.normalized();
        double cosAngle = dirX.dot(Vector(1, 0, 0, 0));
        double angle = std::acos(cosAngle);

        Matrix mat = Matrix::rotate(Vector(1, 0, 0, 0).cross(dirX), angle);

        double xAngle, yAngle, zAngle;
        if (mat.get(2, 0) < 1)
        {
            if (mat.get(2, 0) > -1)
            {
                yAngle = std::asin(-mat.get(2, 0));
                zAngle = std::atan2(mat.get(1, 0), mat.get(0, 0));
                xAngle = std::atan2(mat.get(2, 1), mat.get(2, 2));
            }
            else
            {
                // not a unique solution
                yAngle = M_PI_2;
                zAngle = std::atan2(-mat.get(1, 2), mat.get(1, 1));
                xAngle = 0;
            }
        }
        else
        {
            // not a unique solution
            yAngle = M_PI_2;
            zAngle = std::atan2(-mat.get(1, 2), mat.get(1, 1));
            xAngle = 0;
        }

        rotation = Vector(xAngle, yAngle, zAngle, 0) * 180.0 / M_PI;
    }

    return *this;
}

LightBuilder& LightBuilder::setColor(const Color& newColor)
{
    color = newColor;
    return *this;
}

LightBuilder& LightBuilder::setType(Light::Type newType)
{
    type = newType;
    return *this;
}

LightBuilder &LightBuilder::setId(size_t newId)
{
    id = newId;
    return *this;
}

LightBuilder &LightBuilder::setName(std::string newName)
{
    name = std::move(newName);
    return *this;
}

LightBuilder &LightBuilder::setPosition(const Vector &newPosition)
{
    if (newPosition.getW() != 1.0)
        throw std::runtime_error("bad position vector");

    position = newPosition;
    return *this;
}

LightBuilder &LightBuilder::setRotation(const Vector &newRotation)
{
    if (newRotation.getW() != 0.0)
        throw std::runtime_error("bad rotation vector");

    rotation = newRotation;
    return *this;
}

LightBuilder &LightBuilder::setScale(const Vector &newScale)
{
    if (newScale.getW() != 0.0)
        throw std::runtime_error("bad rotation vector");

    scale = newScale;
    return *this;
}

std::unique_ptr<IObject> LightBuilder::build()
{
    Light light;
    light.setType(type);
    light.setIntensity(intensity);
    light.setColor(color);

    auto object = std::unique_ptr<IObject>(new ObjectAdapter<Light>(id, light));

    object->setName(name);
    object->setPosition(position);
    object->setRotation(rotation);
    object->setScale(scale);

    return object;
}
