#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Core/common/containers/vect_t.hpp"
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

    Vertex project_frustrum(const Vertex& vertex, const Camera& camera);
    Vertex project(const Vertex& vertex, const Camera& camera);

    Vertex vertex_delta(const Vertex& v_start, const Vertex& v_end, unsigned int steps);
    Vertex interpolate(const Vertex& v1, const Vertex& v2, double t);

    vect_t<Vertex> clip_polygon(const vect_t<Vertex>& points);
    vect_t<Vertex> clip_polygon(const vect_t<Vertex>& points, int component);
    vect_t<Vertex> clip_polygon(const vect_t<Vertex>& points, int component, double scale);
}

#endif // VERTEX_HPP
