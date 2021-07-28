#ifndef MESH_HPP
#define MESH_HPP

#include "Core/common/math/Vec.hpp"
#include "Core/common/containers/vect_t.hpp"
#include "Core/Objects/Face.hpp"


namespace Core
{
    struct Mesh
    {
        vect_t<Face> faces;
    };

    Mesh make_mesh(size_t faces_count);
    void destroy(Mesh& mesh);

    bool add_face(Mesh& mesh, const Face& face);
}

#endif // MESH_HPP
