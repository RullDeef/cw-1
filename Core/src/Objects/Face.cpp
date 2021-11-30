#include <Core/Rasterizers/RenderRegion.hpp>
#include "Core/Rasterizers/LineRenderer.hpp"
#include "Core/Objects/Face.hpp"
#include "Core/Objects/Camera.hpp"
#include "Core/RenderParams.hpp"

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

Vec Core::get_center(const Face &face)
{
    return (face.verts[0].position + face.verts[1].position + face.verts[2].position) / 3;
}

Vec Core::get_mean_normal(const Face& face)
{
    return normalized(face.verts[0].normal + face.verts[1].normal + face.verts[2].normal);
}

double Core::side_length(const Face& face, size_t i, size_t j)
{
    Vec pos_i = face.verts[i].position;
    Vec pos_j = face.verts[j].position;

    return length(pos_i - pos_j);
}

Face Core::operator*(const Mat& mat, const Face& face)
{
    Face res = face;

    res.verts[0] = mat * res.verts[0];
    res.verts[1] = mat * res.verts[1];
    res.verts[2] = mat * res.verts[2];

    return res;
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

arr_t<Face, 4> Core::clip_face(const Face& face, double x_aspect, double y_aspect, double left, double right, double top, double bottom)
{
    arr_t<Vertex, 3> verts = make_arr<Vertex, 3>();
    push_back(verts, face.verts[0]);
    push_back(verts, face.verts[1]);
    push_back(verts, face.verts[2]);

    auto clipped = clip_polygon(verts, x_aspect, y_aspect, left, right, top, bottom);
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

    if (type & OcclusionCulling)
    {
        unsigned int code1 = bit_code(p1);
        unsigned int code2 = bit_code(p2);
        unsigned int code3 = bit_code(p3);

        if (code1 & code2 & code3)
            return true;
    }

    if (type & BackfaceCulling)
    {
        p1 = viewport_adjust(camera, p1);
        p2 = viewport_adjust(camera, p2);
        p3 = viewport_adjust(camera, p3);

        Vec norm = Core::cross(p2 - p1, p3 - p1);
        Vec dir = make_dir(0, 0, -1); ///TODO: remove code duplication

        double dot = Core::dot(dir, norm);
        if (dot <= 0.0)
            return true;
    }

    return false;
}

bool Core::culling(const Face& face, const Camera& camera, const RectF& renderViewport, FaceCullingType type)
{
    Vec p1 = project_viewport_frustrum(camera, face.verts[0].position);
    Vec p2 = project_viewport_frustrum(camera, face.verts[1].position);
    Vec p3 = project_viewport_frustrum(camera, face.verts[2].position);

    if (type & OcclusionCulling)
    {
        double dx = renderViewport.left + renderViewport.width / 2.0 - camera.viewport.left - camera.viewport.width / 2.0;
        double dy = renderViewport.top + renderViewport.height / 2.0 - camera.viewport.top - camera.viewport.height / 2.0;

        double left = (dx - renderViewport.width / 2.0) / (camera.viewport.width / 2.0);
        double right = (dx + renderViewport.width / 2.0) / (camera.viewport.width / 2.0);

        double top = (dy - renderViewport.height / 2.0) / (camera.viewport.height / 2.0);
        double bottom = (dy + renderViewport.height / 2.0) / (camera.viewport.height / 2.0);

        unsigned int code1 = bit_code(p1, left, right, top, bottom);
        unsigned int code2 = bit_code(p2, left, right, top, bottom);
        unsigned int code3 = bit_code(p3, left, right, top, bottom);

        if (code1 & code2 & code3)
            return true;
    }

    if (type & BackfaceCulling)
    {
        p1 = viewport_adjust(camera, p1);
        p2 = viewport_adjust(camera, p2);
        p3 = viewport_adjust(camera, p3);

        Vec norm = Core::cross(p2 - p1, p3 - p1);
        Vec dir = make_dir(0, 0, -1);

        double dot = Core::dot(dir, norm);
        if (dot <= 0.0)
            return true;
    }

    return false;
}

StatusCode Core::renderFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face, const Camera &camera, LightingModelType lighting, ColorComputeFn colorComputeFn)
{
    double x_aspect = get_x_aspect(camera.viewport);
    double y_aspect = get_y_aspect(camera.viewport);

    Face projection = project_frustrum(face, camera);
    auto projections = clip_face(projection, x_aspect, y_aspect);

    for (size_t i = 0; i < projections.size; i++)
    {
        Face clip_face = unproject_frustrum(projections.data[i], camera);

        StatusCode result = renderClippedFace(renderTarget, zbuffer, mesh, clip_face, camera, lighting, colorComputeFn);
        if (result != StatusCode::Success)
            return result;
    }

    return StatusCode::Success;
}

StatusCode Core::renderFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const RectF& renderViewport, const Mesh &mesh, Face face, const Camera &camera, LightingModelType lighting, ColorComputeFn colorComputeFn)
{
    double x_aspect = get_x_aspect(camera.viewport);
    double y_aspect = get_y_aspect(camera.viewport);

    double dx = renderViewport.left + renderViewport.width / 2.0 - camera.viewport.left - camera.viewport.width / 2.0;
    double dy = renderViewport.top + renderViewport.height / 2.0 - camera.viewport.top - camera.viewport.height / 2.0;

    double left = (dx - renderViewport.width / 2.0) / (camera.viewport.width / 2.0);
    double right = (dx + renderViewport.width / 2.0) / (camera.viewport.width / 2.0);

    double top = (dy - renderViewport.height / 2.0) / (camera.viewport.height / 2.0);
    double bottom = (dy + renderViewport.height / 2.0) / (camera.viewport.height / 2.0);

    Face projection = project_frustrum(face, camera);
    auto projections = clip_face(projection, x_aspect, y_aspect, left, right, top, bottom);

    for (size_t i = 0; i < projections.size; i++)
    {
        Face clip_face = unproject_frustrum(projections.data[i], camera);

        StatusCode result = renderClippedFace(renderTarget, zbuffer, mesh, clip_face, camera, lighting, colorComputeFn);
        if (result != StatusCode::Success)
            return result;
    }

    return StatusCode::Success;
}

StatusCode Core::renderClippedFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face, const Camera &camera, LightingModelType lighting, ColorComputeFn colorComputeFn)
{
    StatusCode result = StatusCode::Success;
    Face projection = project(face, camera);
    auto regions = make_render_regions(mesh, inverse(camera.model_mat) * mesh.model_mat * face, projection);

    lock(renderTarget);

    if (lighting == LightingModelType::Flat)
    {
        flat_correction(regions, inverse(camera.model_mat) * mesh.model_mat * face); // TODO: check need of mult

        for (size_t i = 0; i < regions.size; i++)
        {
            RenderRegion* region = nullptr;
            if (at(regions, i, region))
                renderFlat(renderTarget, zbuffer, *region, colorComputeFn);
        }
    }
    else if (lighting == LightingModelType::Gouraud)
    {
        for (size_t i = 0; i < regions.size; i++)
        {
            RenderRegion* region = nullptr;
            if (at(regions, i, region))
                renderGouraud(renderTarget, zbuffer, *region, colorComputeFn);
        }
    }
    else if (lighting == LightingModelType::Phong)
    {
        for (size_t i = 0; i < regions.size; i++)
        {
            RenderRegion* region = nullptr;
            if (at(regions, i, region))
                renderPhong(renderTarget, zbuffer, *region, colorComputeFn);
        }
    }
    else
        result = StatusCode::UnsupportedLightingModelType;

    unlock(renderTarget);
    return result;
}

StatusCode Core::renderWireframeFace(RenderTarget& renderTarget, Face face, const Camera& camera, Color color)
{
    return renderWireframeFace(renderTarget, face, camera, to_pixel(color));
}

StatusCode Core::renderWireframeFace(RenderTarget& renderTarget, Face face, const Camera& camera, Pixel color)
{
    Face projection = project_frustrum(face, camera);

    arr_t<Vertex, 3> vertices = make_arr<Vertex, 3>();
    push_back(vertices, projection.verts[0]);
    push_back(vertices, projection.verts[1]);
    push_back(vertices, projection.verts[2]);

    double x_aspect = get_x_aspect(camera.viewport);
    double y_aspect = get_y_aspect(camera.viewport);

    auto clipped = clip_polygon(vertices, x_aspect, y_aspect);
    if (clipped.size >= 3)
    {
        Vertex v1, v2, v3;
        get(clipped, 0, v1);

        for (size_t i = 1; i < clipped.size - 1; i++)
        {
            get(clipped, i, v2);
            get(clipped, i + 1, v3);

            Vec p1 = viewport_adjust(camera, v1.position);
            Vec p2 = viewport_adjust(camera, v2.position);
            Vec p3 = viewport_adjust(camera, v3.position);

            renderLine(renderTarget, p1, p2, color);
            renderLine(renderTarget, p2, p3, color);
            renderLine(renderTarget, p1, p3, color);
        }
    }

    return StatusCode::Success;
}
