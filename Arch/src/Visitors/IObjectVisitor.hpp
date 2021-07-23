#ifndef IOBJECTVISITOR_HPP
#define IOBJECTVISITOR_HPP

#include "IObject.hpp"

namespace Core
{
    class Mesh;
    class Camera;
    class LightSource;
}

// enum class AdapterPolicy;
// template<typename T, AdapterPolicy policy>
// class ObjectAdapter;

class IObjectVisitor
{
public:
    virtual ~IObjectVisitor() = default;

    virtual void visit(ObjectAdapter<Core::Mesh>& mesh) = 0;
    virtual void visit(ObjectAdapter<Core::Camera>& camera) = 0;
    virtual void visit(ObjectAdapter<Core::LightSource>& lightSource) = 0;
};

#endif // IOBJECTVISITOR_HPP
