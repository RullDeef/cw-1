#include "Objects/Mesh.hpp"


Mesh::Mesh(const Core::Mesh& mesh)
    : mesh(mesh), material(mesh.material)
{
}

Mesh::Mesh(Mesh &&temp) noexcept
    : mesh(temp.mesh), material(temp.material)
{
    temp.mesh = Core::make_mesh(0);
}

Mesh::~Mesh()
{
    Core::destroy(mesh);
}

Mesh::operator Core::Mesh() const
{
    Core::Mesh res = mesh;
    res.material = material;
    return res;
}

Material &Mesh::getMaterial()
{
    return material;
}

const Material &Mesh::getMaterial() const
{
    return material;
}

Matrix Mesh::getModelMatrix() const
{
    return mesh.model_mat;
}

void Mesh::setModelMatrix(const Matrix &matrix)
{
    mesh.model_mat = matrix;
}

void Mesh::setMaterial(const Material &newMaterial)
{
    material = newMaterial;
}

void Mesh::setSelected(bool state)
{
    mesh.wireframe = state;
}

bool Mesh::intersects(double &t, const Ray &ray) const
{
    return Core::ray_intersects(t, ray, *this);
}
