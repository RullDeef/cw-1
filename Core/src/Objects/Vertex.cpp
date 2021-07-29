#include "Core/Objects/Vertex.hpp"

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
        vert.normal = normalised(normal);
    else
        vert.normal = normal;
    vert.uv = uv;

    return vert;
}
