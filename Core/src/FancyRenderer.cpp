#include <cmath>
#include "Core/math/Ray.hpp"
#include "Core/math/Plane.hpp"
#include "Core/Objects/Mesh.hpp"
#include "Core/Objects/Material.hpp"
#include "Core/Rasterizers/RectRenderer.hpp"
#include "Core/FancyRenderer.hpp"

using namespace Core;

static bool renderViewportValid(const Rect& viewport, const RenderTarget& renderTarget);
static Color rayTraceRender(const Scene& scene, const Camera& camera, int pixelRow, int pixelCol);
static Color traceRay(Ray ray, const Scene& scene, const Camera& camera, unsigned int depthLeft);
static bool findIntersectionPoint(Mesh*& mesh, Face*& face, double& distance, Ray ray, const Scene& scene);


StatusCode Core::fancyRenderScene(RenderParams renderParams)
{
    if (!renderViewportValid(renderParams.viewport, renderParams.renderTarget))
        return StatusCode::InvalidRenderViewport;

//    double r = rand() % 100 / 100.0;
//    double g = rand() % 100 / 100.0;
//    double b = rand() % 100 / 100.0;
//    Color color = make_color(r, g, b);

    for (int row = renderParams.viewport.top; row < renderParams.viewport.top + renderParams.viewport.height; row++)
    {
        for (int col = renderParams.viewport.left; col < renderParams.viewport.left + renderParams.viewport.width; col++)
        {
            Color color = rayTraceRender(renderParams.scene, renderParams.camera, row, col);
            setPixel(renderParams.renderTarget, row, col, to_pixel(color));
        }
    }

    return StatusCode::Success;
}

static bool renderViewportValid(const Rect& viewport, const RenderTarget& renderTarget)
{
    return is_valid(viewport) && is_inside(get_viewport(renderTarget), viewport);
}

static Color rayTraceRender(const Scene& scene, const Camera& camera, int pixelRow, int pixelCol)
{
    Ray ray = shoot_ray(camera, pixelCol, pixelRow);
    return traceRay(ray, scene, camera, 0);
}

static Color traceRay(Ray ray, const Scene& scene, const Camera& camera, unsigned int depthLeft)
{
    Mesh* mesh;
    Face* face;
    double distance;

    if (findIntersectionPoint(mesh, face, distance, ray, scene))
    {
        Vec position = ray_at(ray, distance);
        Vec view = normalized(position - camera.eye);
        Mat view_mat = inverse(camera.model_mat);
        Vec normal = get_mean_normal(*face);

        return compute_color(mesh->material, scene.lightList, view_mat, view, normal);
    }

    return Colors::black;
}

static bool findIntersectionPoint(Mesh*& mesh, Face*& face, double& distance, Ray ray, const Scene& scene)
{
    distance = std::numeric_limits<double>::infinity();
    mesh = nullptr;
    face = nullptr;

    for (auto node = scene.meshList.head; node; node = node->next)
    {
        Sphere bounding_sphere = get_bounding_sphere(node->value);
        double t;

        if (ray_intersects(t, ray, bounding_sphere) && t < distance)
        {
            mesh = &node->value;
            for (size_t i = 0; i < mesh->faces.size; i++)
            {
                if (ray_intersects(t, ray, mesh->faces.data[i]) && t < distance)
                {
                    distance = t;
                    face = &mesh->faces.data[i];
                }
            }
        }
    }

    return face != nullptr;
}
