#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Core/common/math/Vec.hpp"


namespace Core
{
    struct Camera;

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

    Vertex project(const Vertex& vertex, const Camera& camera);

    Vertex vertex_delta(const Vertex& v_start, const Vertex& v_end, unsigned int steps);
    Vertex interpolate(const Vertex& v1, const Vertex& v2, double t);
}

#endif // VERTEX_HPP
