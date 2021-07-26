#ifndef MESH_HPP
#define MESH_HPP

#include "Core/common/math/Vec.hpp"
#include "Core/common/containers/vect_t.hpp"


namespace Core
{
    struct Vertex
    {
        Vec position;
        Vec normal;
        Vec uv;
    };

    struct Face
    {
        Vertex verts[3];
    };

    struct Mesh
    {
        vect_t<Face> faces;
    };

    Mesh make_mesh(size_t faces_count);
    void destroy(Mesh& mesh);
}

#endif // MESH_HPP
