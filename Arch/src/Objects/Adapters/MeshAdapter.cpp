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
    return false;
    /// TODO: move to mesh wrapper class
//    double tMin = std::numeric_limits<double>::infinity();
//    bool intersects = false;
//
//    for (size_t i = 0; i < mesh.faces.size; i++)
//    {
//        Core::Face face{};
//        if (Core::get(mesh.faces, i, face))
//        {
//            if (Core::ray_intersects(t, ray, face))
//            {
//                intersects = true;
//                tMin = std::min(tMin, t);
//            }
//        }
//    }
//
//    t = tMin;
//    return intersects;
}
