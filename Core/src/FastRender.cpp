#include <Core/Rasterizers/RenderRegion.hpp>
#include "Core/FastRender.hpp"
#include "Core/Rasterizers/LineRenderer.hpp"
#include "Core/RenderTarget/ZBuffer.hpp"
#include "Core/common/math/Mat.hpp"
#include "Core/common/math/Plane.hpp"

using namespace Core;

static void makeBG(RenderTarget& renderTarget);
static StatusCode renderWireframeMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, Camera& camera);
static StatusCode renderFace(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh &mesh, Face face, const Camera& camera);
static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2, Pixel color);
static bool backFaceCulling(const Face& face, const Camera& camera);
static bool oculusCulling(const Face& face, const Camera& camera);

// clipping functions
static Vec projectToFrustrum(const Camera& camera, const Vec& point);
static unsigned int computeBitCode(const Vec& point);

static Pixel recomputeColor(const Vec& normal);
static Pixel recomputeColor(const Vec& normal, const Vec& view, const Material& material);


StatusCode Core::fastRenderScene(RenderParams renderParams)
{
    ZBuffer zbuffer = make_zbuffer(renderParams.renderTarget.width, renderParams.renderTarget.height);
    fill(zbuffer, 1000000);

    makeBG(renderParams.renderTarget);

    for (auto node = renderParams.scene.meshList.head; node; node = node->next)
        renderWireframeMesh(renderParams.renderTarget, zbuffer, node->value, renderParams.camera);

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

static StatusCode renderWireframeMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, Camera& camera)
{
    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);
        renderFace(renderTarget, zbuffer, mesh, *face, camera);
    }

    return StatusCode::Success;
}

static StatusCode renderFace(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh &mesh, Face face, const Camera& camera)
{
    if (oculusCulling(face, camera) || backFaceCulling(face, camera))
        return StatusCode::Success;

    Face projection = project(face, camera);
    auto regions = make_render_regions(mesh, face, projection);

    for (size_t i = 0; i < regions.size; i++)
    {
        RenderRegion* region = nullptr;
        if (at(regions, i, region))
            render(renderTarget, zbuffer, *region, camera);
    }

    return StatusCode::Success;
}

static bool backFaceCulling(const Face& face, const Camera& camera)
{
    Vec p1 = projectToFrustrum(camera, face.verts[0].position);
    Vec p2 = projectToFrustrum(camera, face.verts[1].position);
    Vec p3 = projectToFrustrum(camera, face.verts[2].position);

    Vec norm = Core::cross(p2 - p1, p3 - p1);
    Vec dir = make_dir(0, 0, 1);

    double dot = Core::dot(dir, norm);
    return dot < 0.0;
}

static bool oculusCulling(const Face& face, const Camera& camera)
{
    Vec p1 = projectToFrustrum(camera, face.verts[0].position);
    Vec p2 = projectToFrustrum(camera, face.verts[1].position);
    Vec p3 = projectToFrustrum(camera, face.verts[2].position);

    unsigned int code1 = computeBitCode(p1);
    unsigned int code2 = computeBitCode(p2);
    unsigned int code3 = computeBitCode(p3);

    return code1 & code2 & code3;
}

static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2, Pixel color)
{
    return renderLine(renderTarget, p1.x, p1.y, p2.x, p2.y, color);
}

static Vec projectToFrustrum(const Camera& camera, const Vec& point)
{
    Vec res = camera.mvp * point;

    res.x /= res.z;
    res.y /= res.z;
    res.z = (res.z - camera.near) / (camera.far - camera.near) * 2 - 1;

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

static unsigned int computeBitCode(const Vec& point)
{
    unsigned int code = 0x000000;

    const double side = 1.0;

    code |= (point.x < -side ? 1 : 0) << 0;
    code |= (point.x >  side ? 1 : 0) << 1;
    code |= (point.y < -side ? 1 : 0) << 2;
    code |= (point.y >  side ? 1 : 0) << 3;
    code |= (point.z < -side ? 1 : 0) << 4;
    code |= (point.z >  side ? 1 : 0) << 5;

    return code;
}

static Pixel recomputeColor(const Vec& normal, const Vec& view, const Material& material)
{
    static Vec light_1 = normalised(make_dir(-1, 2, 1));
    static Vec light_2 = normalised(make_dir(3, 4, -2));

    auto lights = make_arr<Vec, 2>();
    push_back(lights, light_1);
    push_back(lights, light_2);

    Color color = compute_color(material, lights, view, normal);
    return to_pixel(color);
}
