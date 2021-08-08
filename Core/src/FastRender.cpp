#include <Core/Rasterizers/RenderRegion.hpp>
#include "Core/FastRender.hpp"
#include "Core/Rasterizers/LineRenderer.hpp"
#include "Core/RenderTarget/ZBuffer.hpp"
#include "Core/common/math/Mat.hpp"

using namespace Core;

static void makeBG(RenderTarget& renderTarget);

static StatusCode renderMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, Camera& camera,
                             RenderParams::LightingModelType lighting, FaceCullingType cullingType);
static StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera,
                                      FaceCullingType cullingType);

static StatusCode renderFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face,
                             const Camera &camera, RenderParams::LightingModelType lighting);
static StatusCode renderClippedFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face,
                                    const Camera &camera, RenderParams::LightingModelType lighting);
static StatusCode renderWireframeFace(RenderTarget& renderTarget, Face face, const Camera& camera);

static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2, Pixel color);

static Pixel recomputeColor(const Vec& normal);
static Pixel recomputeColor(const Vec& normal, const Vec& view, const Material& material);


StatusCode Core::fastRenderScene(RenderParams renderParams)
{
    ZBuffer zbuffer = make_zbuffer(renderParams.renderTarget.width, renderParams.renderTarget.height);
    fill(zbuffer, 1000000);

    makeBG(renderParams.renderTarget);

    for (auto node = renderParams.scene.meshList.head; node; node = node->next)
        if (node->value.fill)
            renderMesh(renderParams.renderTarget, zbuffer, node->value, renderParams.camera,
                       renderParams.sceneLightingModel, renderParams.faceCullingType);

    for (auto node = renderParams.scene.meshList.head; node; node = node->next)
        if (node->value.wireframe)
            renderWireframeMesh(renderParams.renderTarget, node->value, renderParams.camera,
                                renderParams.faceCullingType);

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

static StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera,
                                      FaceCullingType cullingType)
{
    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);

        if (!culling(*face, camera, cullingType))
            renderWireframeFace(renderTarget, *face, camera);
    }

    return StatusCode::Success;
}

static StatusCode renderMesh(RenderTarget& renderTarget, ZBuffer& zbuffer,
                             const Mesh& mesh, Camera& camera, RenderParams::LightingModelType lighting,
                             FaceCullingType cullingType)
{
    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);

        if (!culling(*face, camera, cullingType))
            renderFace(renderTarget, zbuffer, mesh, *face, camera, lighting);
    }

    return StatusCode::Success;
}

static StatusCode renderWireframeFace(RenderTarget& renderTarget, Face face, const Camera& camera)
{
    Pixel color = to_pixel(Colors::orange);
    Face projection = project_frustrum(face, camera);

    arr_t<Vertex, 3> vertices = make_arr<Vertex, 3>();
    push_back(vertices, projection.verts[0]);
    push_back(vertices, projection.verts[1]);
    push_back(vertices, projection.verts[2]);

    double x_aspect = 1.0; /// TODO: extract method
    double y_aspect = 1.0;
    if (camera.viewport.width < camera.viewport.height)
        x_aspect *= double(camera.viewport.height) / camera.viewport.width;
    else
        y_aspect *= double(camera.viewport.width) / camera.viewport.height;

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

static StatusCode renderFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face,
                             const Camera &camera, RenderParams::LightingModelType lighting)
{
    double x_aspect = 1.0;
    double y_aspect = 1.0;
    if (camera.viewport.width < camera.viewport.height)
        x_aspect *= double(camera.viewport.height) / camera.viewport.width;
    else
        y_aspect *= double(camera.viewport.width) / camera.viewport.height;

    Face projection = project_frustrum(face, camera);
    auto projections = clip_face(projection, x_aspect, y_aspect);

    for (size_t i = 0; i < projections.size; i++)
    {
        Face clip_face = unproject_frustrum(projections.data[i], camera);

        /// TODO: do not ignore status code
        renderClippedFace(renderTarget, zbuffer, mesh, clip_face, camera, lighting);
    }

    return StatusCode::Success;
}

static StatusCode renderClippedFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face,
                                    const Camera &camera, RenderParams::LightingModelType lighting)
{
    Face projection = project(face, camera);

    if (lighting == RenderParams::LightingModelType::FlatModelType)
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
    else if (lighting == RenderParams::LightingModelType::GouraudModelType)
    {
        auto regions = make_render_regions(mesh, face, projection);

        for (size_t i = 0; i < regions.size; i++)
        {
            RenderRegion* region = nullptr;
            if (at(regions, i, region))
                renderGouraud(renderTarget, zbuffer, *region, camera);
        }
    }
    else if (lighting == RenderParams::LightingModelType::PhongModelType)
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

static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2, Pixel color)
{
    return renderLine(renderTarget, p1.x, p1.y, p2.x, p2.y, color);
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
