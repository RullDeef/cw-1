#ifndef IOBJECTVISITOR_HPP
#define IOBJECTVISITOR_HPP

#include "IObject.hpp"


class IObjectVisitor
{
public:
    virtual ~IObjectVisitor() = default;

    virtual visit(ObjectAdapter<Mesh>& mesh) = 0;
    virtual visit(ObjectAdapter<Camera>& camera) = 0;
    virtual visit(ObjectAdapter<LightSource>& lightSource) = 0;
};

#endif // IOBJECTVISITOR_HPP
