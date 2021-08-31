#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Core/containers/arr_t.hpp"
#include "Core/containers/vect_t.hpp"
#include "Core/math/Vec.hpp"
#include "Core/math/Mat.hpp"


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

    Vertex operator*(const Mat& mat, const Vertex& vertex);

    Vertex project_viewport_frustrum(const Vertex& vertex, const Camera& camera);
    Vertex project_frustrum(const Vertex& vertex, const Camera& camera);
    Vertex project(const Vertex& vertex, const Camera& camera);

    Vertex unproject_frustrum(const Vertex& vertex, const Camera& camera);

    Vertex vertex_delta(const Vertex& v_start, const Vertex& v_end, unsigned int steps);
    Vertex interpolate(const Vertex& v1, const Vertex& v2, double t);

    vect_t<Vertex> clip_polygon(const vect_t<Vertex>& points, double x_aspect = 1.0, double y_aspect = 1.0);
    vect_t<Vertex> clip_polygon(const vect_t<Vertex>& points, double aspect, int component);
    vect_t<Vertex> clip_polygon(const vect_t<Vertex>& points, int component, double scale);

    arr_t<Vertex, 6> clip_polygon(const arr_t<Vertex, 3>& points, double x_aspect = 1.0, double y_aspect = 1.0, double left = -1.0, double right = 1.0, double top = -1.0, double bottom = 1.0);
    arr_t<Vertex, 6> clip_polygon(const arr_t<Vertex, 6>& points, double aspect, int component, double lower = -1.0, double upper = 1.0);
    arr_t<Vertex, 6> clip_polygon(const arr_t<Vertex, 6>& points, int component, double scale, double offset = 0.0);
}

#endif // VERTEX_HPP
