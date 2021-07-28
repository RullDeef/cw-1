#include "Core/Objects/Mesh.hpp"

using namespace Core;


Mesh Core::make_mesh(size_t faces_count)
{
    Mesh mesh{};

    mesh.faces = make_vect<Face>(faces_count);

    return mesh;
}

void Core::destroy(Mesh& mesh)
{
    destroy(mesh.faces);
}

bool Core::add_face(Mesh &mesh, const Face &face)
{
    return push_back(mesh.faces, face);
}
