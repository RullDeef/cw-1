#include <Core/common/math/Ray.hpp>
#include "Objects/Adapters/MeshAdapter.hpp"
#include "Visitors/IObjectVisitor.hpp"


ObjectAdapter<Mesh>::ObjectAdapter(size_t id, Mesh mesh)
        : IObject(id), mesh(std::move(mesh))
{
}

ObjectAdapter<Mesh>::~ObjectAdapter()
{
}

Mesh& ObjectAdapter<Mesh>::getAdaptee()
{
    mesh.setSelected(isSelected());
    return mesh;
}

const Mesh& ObjectAdapter<Mesh>::getAdaptee() const
{
    ((Mesh&)mesh).setSelected(isSelected());
    return mesh;
}

void ObjectAdapter<Mesh>::accept(IObjectVisitor& visitor)
{
    mesh.setSelected(isSelected());
    visitor.visit(*this);
}

bool ObjectAdapter<Mesh>::intersects(double &t, const Ray &ray)
{
    return mesh.intersects(t, ray);
}
