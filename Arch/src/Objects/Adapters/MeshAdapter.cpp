#include "Core/Objects/Mesh.hpp"
#include "Objects/Adapters/MeshAdapter.hpp"
#include "Visitors/IObjectVisitor.hpp"


ObjectAdapter<Core::Mesh>::ObjectAdapter(size_t id, Core::Mesh mesh, AdapterPolicy policy)
        : IObject(id), mesh(mesh), policy(policy)
{
}

ObjectAdapter<Core::Mesh>::~ObjectAdapter()
{
    if (policy == AdapterPolicy::StrongOwnership)
    {
        Core::destroy(mesh);
    }
}

Core::Mesh& ObjectAdapter<Core::Mesh>::getAdaptee()
{
    return mesh;
}

const Core::Mesh& ObjectAdapter<Core::Mesh>::getAdaptee() const
{
    return mesh;
}

void ObjectAdapter<Core::Mesh>::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}

bool ObjectAdapter<Core::Mesh>::intersects(double &t, const Core::Ray &ray)
{
    /// TODO: implement

    t = 10;
    return true;
}
