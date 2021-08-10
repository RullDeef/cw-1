#ifndef IOBJECTBUILDER_HPP
#define IOBJECTBUILDER_HPP

#include <memory>
#include "Objects/IObject.hpp"


class IObjectBuilder
{
public:
    virtual ~IObjectBuilder() = default;

    virtual std::unique_ptr<IObject> build() = 0;
};

#endif // IOBJECTBUILDER_HPP
