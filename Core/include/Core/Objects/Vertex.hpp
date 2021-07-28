#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Core/common/math/Vec.hpp"


namespace Core
{
    struct Vertex
    {
        Vec position;
        Vec normal;
        Vec uv;
    };

    Vertex make_vertex();
    Vertex make_vertex(Vec position);
    Vertex make_vertex(Vec position, Vec normal);
    Vertex make_vertex(Vec position, Vec normal, Vec uv);
}

#endif // VERTEX_HPP
