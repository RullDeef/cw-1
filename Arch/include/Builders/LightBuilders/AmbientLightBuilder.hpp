#ifndef AMBIENTLIGHTBUILDER_HPP
#define AMBIENTLIGHTBUILDER_HPP

#include "Builders/IObjectBuilder.hpp"


class AmbientLightBuilder : public IObjectBuilder
{
public:
    std::unique_ptr<IObject> build() override;
};

#endif // AMBIENTLIGHTBUILDER_HPP
