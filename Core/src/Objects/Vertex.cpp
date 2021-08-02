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

Vertex Core::project(const Vertex &vertex, const Camera &camera)
{
    Vertex result = vertex;

    result.position = project_point(camera, vertex.position);
    result.position.x = int(result.position.x);
    result.position.y = int(result.position.y);

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
