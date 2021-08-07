#include <Core/Rasterizers/RenderRegion.hpp>
#include "Core/FastRender.hpp"
#include "Core/Rasterizers/LineRenderer.hpp"
#include "Core/RenderTarget/ZBuffer.hpp"
#include "Core/common/math/Mat.hpp"

using namespace Core;

static void makeBG(RenderTarget& renderTarget);

static StatusCode renderMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, Camera& camera);
static StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera);

static StatusCode renderFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face,
                             const Camera &camera, LightingModelType lighting);
static StatusCode renderWireframeFace(RenderTarget& renderTarget, Face face, const Camera& camera);

static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2, Pixel color);

static bool backFaceCulling(const Face& face, const Camera& camera);
static bool occlusionCulling(const Face& face, const Camera& camera);

// clipping functions
static Vec projectToFrustrum(const Camera& camera, const Vec& point);
static unsigned int computeBitCode(const Vec& point, double near, double far);

static Pixel recomputeColor(const Vec& normal);
static Pixel recomputeColor(const Vec& normal, const Vec& view, const Material& material);


StatusCode Core::fastRenderScene(RenderParams renderParams)
{
    ZBuffer zbuffer = make_zbuffer(renderParams.renderTarget.width, renderParams.renderTarget.height);
    fill(zbuffer, 1000000);

    makeBG(renderParams.renderTarget);

    for (auto node = renderParams.scene.meshList.head; node; node = node->next)
        renderWireframeMesh(renderParams.renderTarget, node->value, renderParams.camera);

    destroy(zbuffer);
    return StatusCode::Success;
}

static void makeBG(RenderTarget& renderTarget)
{
    for (size_t row = 0; row < renderTarget.height; row++)
    {
        for (size_t col = 0; col < renderTarget.width; col++)
        {
            if (true || ((row / 64) % 2 == 0) ^ ((col / 64) % 2 == 0))
                setPixel(renderTarget, row, col, to_pixel(Colors::black));
            else
                setPixel(renderTarget, row, col, { 64u, 0u, 64u, 255u });
        }
    }
}

static StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera)
{
    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);
        renderWireframeFace(renderTarget, *face, camera);
    }

    return StatusCode::Success;
}

static StatusCode renderMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, Camera& camera)
{
    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);
        renderFace(renderTarget, zbuffer, mesh, *face, camera, LightingModelType::PhongModelType);
    }

    return StatusCode::Success;
}

static StatusCode renderWireframeFace(RenderTarget& renderTarget, Face face, const Camera& camera)
{
    // if (occlusionCulling(face, camera) || backFaceCulling(face, camera))
    //     return StatusCode::Success;

    Pixel color = to_pixel(Colors::orange);
    Face projection = project_frustrum(face, camera);

    vect_t<Vertex> vertices = make_vect<Vertex>(3);
    vertices.size = 3;
    set(vertices, 0, projection.verts[0]);
    set(vertices, 1, projection.verts[1]);
    set(vertices, 2, projection.verts[2]);

    auto clipped = clip_polygon(vertices);
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

    destroy(clipped);
    destroy(vertices);
    return StatusCode::Success;
}

static StatusCode
renderFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face, const Camera &camera,
           LightingModelType lighting)
{
    if (occlusionCulling(face, camera) || backFaceCulling(face, camera))
        return StatusCode::Success;

    Face projection = project(face, camera);

    if (lighting == LightingModelType::FlatModelType)
    {
//        auto regions = make_flat_render_regions(mesh, face, projection);
//
//        for (size_t i = 0; i < regions.size; i++)
//        {
//            RenderRegion* region = nullptr;
//            /// TODO: implement later
//            if (at(regions, i, region))
//                renderFlat(renderTarget, zbuffer, *region, camera);
//        }
    }
    else if (lighting == LightingModelType::GouraudModelType)
    {
        auto regions = make_render_regions(mesh, face, projection);

        for (size_t i = 0; i < regions.size; i++)
        {
            RenderRegion* region = nullptr;
            if (at(regions, i, region))
                renderGouraud(renderTarget, zbuffer, *region, camera);
        }
    }
    else if (lighting == LightingModelType::PhongModelType)
    {
        auto regions = make_render_regions(mesh, face, projection);

        for (size_t i = 0; i < regions.size; i++)
        {
            RenderRegion* region = nullptr;
            if (at(regions, i, region))
                renderPhong(renderTarget, zbuffer, *region, camera);
        }
    }
    else
        return StatusCode::UnsupportedLightingModelType;

    return StatusCode::Success;
}

static bool backFaceCulling(const Face& face, const Camera& camera)
{
    Vec p1 = projectToFrustrum(camera, face.verts[0].position);
    Vec p2 = projectToFrustrum(camera, face.verts[1].position);
    Vec p3 = projectToFrustrum(camera, face.verts[2].position);

    Vec norm = Core::cross(p2 - p1, p3 - p1);
    Vec dir = make_dir(0, 0, -1);

    double dot = Core::dot(dir, norm);
    return dot < 0.0;
}

static bool occlusionCulling(const Face& face, const Camera& camera)
{
    Vec p1 = projectToFrustrum(camera, face.verts[0].position);
    Vec p2 = projectToFrustrum(camera, face.verts[1].position);
    Vec p3 = projectToFrustrum(camera, face.verts[2].position);

    unsigned int code1 = computeBitCode(p1, camera.near, camera.far);
    unsigned int code2 = computeBitCode(p2, camera.near, camera.far);
    unsigned int code3 = computeBitCode(p3, camera.near, camera.far);

    return code1 & code2 & code3;
}

static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2, Pixel color)
{
    return renderLine(renderTarget, p1.x, p1.y, p2.x, p2.y, color);
}

static Vec projectToFrustrum(const Camera& camera, const Vec& point)
{
    Vec res = camera.mvp * point;
    //perspective_adjust(res);

    // TODO: вынести функции по работе с вьюпортом
#if USE_MIN_FIT
    if (camera.viewport.width > camera.viewport.height)
        res.x *= double(camera.viewport.height) / camera.viewport.width;
    else
        res.y *= double(camera.viewport.width) / camera.viewport.height;
#else
    if (camera.viewport.width > camera.viewport.height)
        res.y *= double(camera.viewport.height) / camera.viewport.width;
    else
        res.x *= double(camera.viewport.width) / camera.viewport.height;
#endif

    return res;
}

static unsigned int computeBitCode(const Vec& point, double near, double far)
{
    unsigned int code = 0x000000;

    code |= (point.x < -point.w ? 1 : 0) << 0;
    code |= (point.x >  point.w ? 1 : 0) << 1;
    code |= (point.y < -point.w ? 1 : 0) << 2;
    code |= (point.y >  point.w ? 1 : 0) << 3;
    code |= (point.z <  near ? 1 : 0) << 4;
    code |= (point.z >  far ? 1 : 0) << 5;

    return code;
}

//static Pixel recomputeColor(const Vec& normal, const Vec& view, const Material& material)
//{
//    static Vec light_1 = normalized(make_dir(-1, 2, 1));
//    static Vec light_2 = normalized(make_dir(3, 4, -2));
//
//    auto lights = make_arr<Vec, 2>();
//    push_back(lights, light_1);
//    push_back(lights, light_2);
//
//    Color color = Colors::white; // compute_color(material, lights, view, normal);
//    return to_pixel(color);
//}
