#ifndef LIGHTBUILDER_HPP
#define LIGHTBUILDER_HPP

#include "Builders/IObjectBuilder.hpp"
#include "Objects/Light.hpp"


class LightBuilder : public IObjectBuilder
{
public:
    LightBuilder& setIntensity(double newIntensity);
    LightBuilder& setDirection(const Vector& newDirection);
    LightBuilder& setColor(const Color& newColor);

    LightBuilder& setType(Light::Type newType);

    ///TODO: get rid of code duplicating in all builder classes (maybe using prototype pattern for temporary generated object)
    LightBuilder& setId(size_t newId);
    LightBuilder& setName(std::string newName);
    LightBuilder& setPosition(const Vector& newPosition);
    LightBuilder& setRotation(const Vector& newRotation);
    LightBuilder& setScale(const Vector& newScale);

    std::unique_ptr<IObject> build() override;

private:
    Light::Type type = Core::LightType::Ambient;
    double intensity = 0.25;
    Color color = Color::white();

    size_t id = 0;
    std::string name;
    Vector position = Vector(0, 0, 0, 1);
    Vector rotation = Vector(0, 0, 0, 0);
    Vector scale = Vector(1, 1, 1, 0);
};

#endif // LIGHTBUILDER_HPP
