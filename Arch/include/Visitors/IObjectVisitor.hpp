#ifndef IOBJECTVISITOR_HPP
#define IOBJECTVISITOR_HPP

#include "Objects/IObject.hpp"

class Mesh;
class Camera;
class Light;

template<typename T>
class ObjectAdapter;


class IObjectVisitor
{
public:
    virtual ~IObjectVisitor() = default;

    virtual void visit(ObjectAdapter<Mesh>& mesh) = 0;
    virtual void visit(ObjectAdapter<Camera>& camera) = 0;
    virtual void visit(ObjectAdapter<Light>& lightSource) = 0;
};

#endif // IOBJECTVISITOR_HPP
