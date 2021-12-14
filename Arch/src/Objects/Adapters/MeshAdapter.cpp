#include <Core/math/Ray.hpp>
#include "Objects/Adapters/MeshAdapter.hpp"
#include "Visitors/IObjectVisitor.hpp"


ObjectAdapter<Mesh>::ObjectAdapter(size_t id, Mesh mesh)
        : IObject(id), mesh(std::move(mesh))
{
}

ObjectAdapter<Mesh>::~ObjectAdapter() = default;

Mesh& ObjectAdapter<Mesh>::getAdaptee()
{
    return mesh;
}

const Mesh& ObjectAdapter<Mesh>::getAdaptee() const
{
    return mesh;
}

void ObjectAdapter<Mesh>::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}

bool ObjectAdapter<Mesh>::intersects(double &t, const Ray &ray)
{
    return mesh.intersects(t, ray);
}

void ObjectAdapter<Mesh>::onVisibilityChange()
{
    IObject::onVisibilityChange();

    mesh.setVisible(isVisible());
}

void ObjectAdapter<Mesh>::onSelectionChange()
{
    IObject::onSelectionChange();

    mesh.setSelected(isSelected());
}

void ObjectAdapter<Mesh>::onTransformChange()
{
    IObject::onTransformChange();

    mesh.setModelMatrix(getTransform());
}
