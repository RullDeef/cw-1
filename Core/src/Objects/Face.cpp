#include "Core/Objects/Face.hpp"

using namespace Core;


Face Core::make_face()
{
    Face face{};

    face.verts[0] = make_vertex();
    face.verts[1] = make_vertex();
    face.verts[2] = make_vertex();

    return face;
}

Face Core::make_face(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
    Face face{};

    face.verts[0] = v1;
    face.verts[1] = v2;
    face.verts[2] = v3;

    return face;
}

Face Core::make_face(const Vertex* vArr)
{
    Face face{};

    face.verts[0] = vArr[0];
    face.verts[1] = vArr[1];
    face.verts[2] = vArr[2];

    return face;
}
