#ifndef MESH_HPP
#define MESH_HPP

#include "ext_math.hpp"
#include "vect_t.hpp"


namespace Core
{
    struct Vertex
    {
        vec position;
        vec normal;
        vec uv;
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
