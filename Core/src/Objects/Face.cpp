#include "Core/Objects/Face.hpp"
#include "Core/Objects/Camera.hpp"

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

Face Core::project_viewport_frustrum(const Face& face, const Camera& camera)
{
    Face result = face;

    result.verts[0] = project_viewport_frustrum(result.verts[0], camera);
    result.verts[1] = project_viewport_frustrum(result.verts[1], camera);
    result.verts[2] = project_viewport_frustrum(result.verts[2], camera);

    return result;
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

Face Core::unproject_frustrum(const Face& face, const Camera& camera)
{
    Face result = face;

    result.verts[0] = unproject_frustrum(result.verts[0], camera);
    result.verts[1] = unproject_frustrum(result.verts[1], camera);
    result.verts[2] = unproject_frustrum(result.verts[2], camera);

    return result;
}

arr_t<Face, 4> Core::clip_face(const Face& face, double x_aspect, double y_aspect)
{
    arr_t<Vertex, 3> verts = make_arr<Vertex, 3>();
    push_back(verts, face.verts[0]);
    push_back(verts, face.verts[1]);
    push_back(verts, face.verts[2]);

    auto clipped = clip_polygon(verts, x_aspect, y_aspect);
    auto result = make_arr<Face, 4>();

    if (clipped.size >= 3)
    {
        Vertex v1, v2, v3;
        get(clipped, 0, v1);

        for (size_t i = 1; i < clipped.size - 1; i++)
        {
            get(clipped, i, v2);
            get(clipped, i + 1, v3);

            push_back(result, make_face(v1, v2, v3));
        }
    }

    return result;
}

bool Core::culling(const Face& face, const Camera& camera, FaceCullingType type)
{
    Vec p1 = project_viewport_frustrum(camera, face.verts[0].position);
    Vec p2 = project_viewport_frustrum(camera, face.verts[1].position);
    Vec p3 = project_viewport_frustrum(camera, face.verts[2].position);

    if (type & OcclusionCullingType)
    {
        unsigned int code1 = bit_code(p1);
        unsigned int code2 = bit_code(p2);
        unsigned int code3 = bit_code(p3);

        if (code1 & code2 & code3)
            return true;
    }

    if (type & BackfaceCullingType)
    {
        Vec norm = Core::cross(p2 - p1, p3 - p1);
        Vec dir = make_dir(0, 0, -1);

        double dot = Core::dot(dir, norm);
        if (dot < 0.0)
            return true;
    }

    return false;
}
