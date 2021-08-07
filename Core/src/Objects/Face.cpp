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

    if (is_zero(v1.normal) || is_zero(v2.normal) || is_zero(v3.normal))
        recalc_normal(face);

    return face;
}

Face Core::make_face(const Vertex* vArr)
{
    Face face{};

    face.verts[0] = vArr[0];
    face.verts[1] = vArr[1];
    face.verts[2] = vArr[2];

    if (is_zero(vArr[0].normal) || is_zero(vArr[1].normal) || is_zero(vArr[2].normal))
        recalc_normal(face);

    return face;
}

void Core::recalc_normal(Face &face)
{
    Vec v1 = face.verts[1].position - face.verts[0].position;
    Vec v2 = face.verts[2].position - face.verts[0].position;

    Vec normal = normalized(cross(v1, v2));

    face.verts[0].normal = normal;
    face.verts[1].normal = normal;
    face.verts[2].normal = normal;
}

Face Core::project_frustrum(const Face &face, const Camera &camera)
{
    Face result = face;

    result.verts[0] = project_frustrum(result.verts[0], camera);
    result.verts[1] = project_frustrum(result.verts[1], camera);
    result.verts[2] = project_frustrum(result.verts[2], camera);

    return result;
}

Face Core::project(const Face &face, const Camera &camera)
{
    Face result = face;

    result.verts[0] = project(result.verts[0], camera);
    result.verts[1] = project(result.verts[1], camera);
    result.verts[2] = project(result.verts[2], camera);

    return result;
}
