#include "Objects/Mesh.hpp"


Mesh::Mesh(const Core::Mesh& mesh)
    : mesh(mesh)
{
}

Mesh::Mesh(Mesh &&temp) noexcept
    : mesh(temp.mesh)
{
    temp.mesh = Core::make_mesh(0);
}

Mesh::~Mesh()
{
    Core::destroy(mesh);
}

Mesh::operator Core::Mesh() const
{
    return mesh;
}
