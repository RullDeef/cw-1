#include <Core/common/math/Ray.hpp>
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
    double tMin = std::numeric_limits<double>::infinity();
    bool intersects = false;

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        Core::Face face{};
        if (Core::get(mesh.faces, i, face))
        {
            if (Core::ray_intersects(t, ray, face))
            {
                intersects = true;
                tMin = std::min(tMin, t);
            }
        }
    }

    t = tMin;
    return intersects;
}
