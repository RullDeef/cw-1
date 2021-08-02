#include "Visitors/Transformer.hpp"
#include "Objects/Adapters/MeshAdapter.hpp"


Transformer::Transformer(double dx, double dy, double dz)
    : dx(dx), dy(dy), dz(dz)
{
}

void Transformer::visit(ObjectAdapter<Core::Mesh> &mesh)
{
    Core::Mesh& adaptee = mesh.getAdaptee();
    auto mat = Core::make_mat_translation(dx, dy, dz);

    adaptee.model_mat = mat * adaptee.model_mat;
}
