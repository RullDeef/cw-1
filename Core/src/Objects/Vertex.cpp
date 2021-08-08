#include "Core/Objects/Vertex.hpp"
#include "Core/Objects/Camera.hpp"

using namespace Core;


Vertex Core::make_vertex()
{
    return make_vertex(make_pos());
}

Vertex Core::make_vertex(Vec position)
{
    return make_vertex(position, make_dir(1, 0, 0));
}

Vertex Core::make_vertex(Vec position, Vec normal)
{
    return make_vertex(position, normal, make_dir());
}

Vertex Core::make_vertex(Vec position, Vec normal, Vec uv)
{
    Vertex vert{};

    vert.position = position;
    if (!is_zero(normal))
        vert.normal = normalized(normal);
    else
        vert.normal = normal;
    vert.uv = uv;

    return vert;
}

Vertex Core::project_viewport_frustrum(const Vertex& vertex, const Camera& camera)
{
    Vertex result = vertex;

    result.position = project_viewport_frustrum(camera, vertex.position);

    return result;
}

Vertex Core::project_frustrum(const Vertex& vertex, const Camera& camera)
{
    Vertex result = vertex;

    result.position = project_frustrum(camera, vertex.position);

    return result;
}

Vertex Core::project(const Vertex &vertex, const Camera &camera)
{
    Vertex result = vertex;

    result.position = project_point(camera, vertex.position);
    result.position.x = int(result.position.x);
    result.position.y = int(result.position.y);

    return result;
}

Vertex Core::unproject_frustrum(const Vertex& vertex, const Camera& camera)
{
    Vertex result = vertex;

    result.position = unproject_frustrum(camera, vertex.position);

    return result;
}

Vertex Core::vertex_delta(const Vertex &v_start, const Vertex &v_end, unsigned int steps)
{
    Vertex res{};

    res.position = (v_end.position - v_start.position) / steps;
    res.normal = (v_end.normal - v_start.normal) / steps;

    return res;
}

Vertex Core::interpolate(const Vertex &v1, const Vertex &v2, double t)
{
    Vertex res{};

    res.position = interpolate(v1.position, v2.position, t);
    res.normal = interpolate(v1.normal, v2.normal, t);

    return res;
}

vect_t<Vertex> Core::clip_polygon(const vect_t<Vertex>& points, double x_aspect, double y_aspect)
{
    vect_t<Vertex> result_1 = clip_polygon(points, x_aspect, 0);
    if (result_1.size == 0)
        return result_1;

    vect_t<Vertex> result_2 = clip_polygon(result_1, y_aspect, 1);
    destroy(result_1);
    if (result_2.size == 0)
        return result_2;

    vect_t<Vertex> result_3 = clip_polygon(result_2, 1.0, 2);
    destroy(result_2);

    return result_3;
}

vect_t<Vertex> Core::clip_polygon(const vect_t<Vertex>& points, double aspect, int component)
{
    vect_t<Vertex> result_1 = clip_polygon(points, component, 1.0 * aspect);

    if (result_1.size == 0)
        return result_1;

    vect_t<Vertex> result_2 = clip_polygon(result_1, component, -1.0 * aspect);
    destroy(result_1);

    return result_2;
}

vect_t<Vertex> Core::clip_polygon(const vect_t<Vertex>& points, int component, double scale)
{
    auto result = make_vect<Vertex>(points.size);

    Vertex prevVert{};
    get(points, points.size - 1, prevVert);
    double prevVal = scale * get(prevVert.position, component);
    bool prevInside = prevVal <= prevVert.position.w;

    for (size_t i = 0; i < points.size; i++)
    {
        Vertex currVert{};
        get(points, i, currVert);
        double currVal = scale * get(currVert.position, component);
        bool currInside = currVal <= currVert.position.w;

        if (prevInside ^ currInside)
        {
            double factor = (prevVert.position.w - prevVal) / ((prevVert.position.w - prevVal) - (currVert.position.w - currVal));
            Vertex intersection = interpolate(prevVert, currVert, factor);
            push_back(result, intersection);
        }

        if (currInside)
            push_back(result, currVert);

        prevVert = currVert;
        prevVal = currVal;
        prevInside = currInside;
    }

    return result;
}

arr_t<Vertex, 6> Core::clip_polygon(const arr_t<Vertex, 3>& points, double x_aspect, double y_aspect)
{
    auto result = make_arr<Vertex, 6>();
    push_back(result, points.data[0]);
    push_back(result, points.data[1]);
    push_back(result, points.data[2]);

    result = clip_polygon(result, x_aspect, 0);
    if (result.size == 0)
        return result;

    result = clip_polygon(result, y_aspect, 1);
    if (result.size == 0)
        return result;

    result = clip_polygon(result, 1.0, 2);
    return result;
}

arr_t<Vertex, 6> Core::clip_polygon(const arr_t<Vertex, 6>& points, double aspect, int component)
{
    arr_t<Vertex, 6> result = clip_polygon(points, component, 1.0 * aspect);
    if (result.size == 0)
        return result;

    return clip_polygon(result, component, -1.0 * aspect);
}

arr_t<Vertex, 6> Core::clip_polygon(const arr_t<Vertex, 6>& points, int component, double scale)
{
    auto result = make_arr<Vertex, 6>();

    Vertex prevVert{};
    get(points, points.size - 1, prevVert);
    double prevVal = scale * get(prevVert.position, component);
    bool prevInside = prevVal <= prevVert.position.w;

    for (size_t i = 0; i < points.size; i++)
    {
        Vertex currVert{};
        get(points, i, currVert);
        double currVal = scale * get(currVert.position, component);
        bool currInside = currVal <= currVert.position.w;

        if (prevInside ^ currInside)
        {
            double factor = (prevVert.position.w - prevVal) / ((prevVert.position.w - prevVal) - (currVert.position.w - currVal));
            Vertex intersection = interpolate(prevVert, currVert, factor);
            push_back(result, intersection);
        }

        if (currInside)
            push_back(result, currVert);

        prevVert = currVert;
        prevVal = currVal;
        prevInside = currInside;
    }

    return result;
}
