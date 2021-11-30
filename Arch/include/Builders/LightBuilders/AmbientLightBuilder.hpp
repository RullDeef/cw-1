#ifndef AMBIENTLIGHTBUILDER_HPP
#define AMBIENTLIGHTBUILDER_HPP

#include "Builders/IObjectBuilder.hpp"


class AmbientLightBuilder : public IObjectBuilder
{
public:
    ///TODO: get rid of code duplicating in all builder classes (maybe using prototype pattern for temporary generated object)
    AmbientLightBuilder& setId(size_t newId);
    AmbientLightBuilder& setName(std::string newName);
    AmbientLightBuilder& setPosition(const Vector& newPosition);
    AmbientLightBuilder& setRotation(const Vector& newRotation);
    AmbientLightBuilder& setScale(const Vector& newScale);

    std::unique_ptr<IObject> build() override;

private:
    size_t id;
    std::string name;
    Vector position = Vector(0, 0, 0, 1);
    Vector rotation = Vector(0, 0, 0, 0);
    Vector scale = Vector(1, 1, 1, 0);
};

#endif // AMBIENTLIGHTBUILDER_HPP
