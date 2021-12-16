#include <cmath>
#include "Core/math/Ray.hpp"
#include "Core/math/Plane.hpp"
#include "Core/Objects/Mesh.hpp"
#include "Core/Objects/Material.hpp"
#include "Core/Rasterizers/RectRenderer.hpp"
#include "Core/FancyRenderer.hpp"

using namespace Core;

static bool renderViewportValid(const RectI& viewport, const RenderTarget& renderTarget);
static Color rayTraceRender(const Scene& scene, const Camera& camera, int pixelRow, int pixelCol);
static std::pair<double, Color> traceRay(Ray ray, const Scene& scene, const Camera& camera, int depthLeft);
static bool findIntersectionPoint(Mesh*& mesh, Face*& face, double& distance, Ray ray, const Scene& scene);


StatusCode Core::fancyRenderScene(RenderParams renderParams)
{
    if (!renderViewportValid(renderParams.viewport, renderParams.renderTarget))
        return StatusCode::InvalidRenderViewport;

    const int rowSpan = 1;
    const int colSpan = 1;

    for (int row = renderParams.viewport.top; row < renderParams.viewport.top + renderParams.viewport.height; row += rowSpan)
    {
        for (int col = renderParams.viewport.left; col < renderParams.viewport.left + renderParams.viewport.width; col += colSpan)
        {
            Color color = rayTraceRender(renderParams.scene, renderParams.camera, row, col);

            for (int dr = 0; dr < rowSpan; dr++)
                for (int dc = 0; dc < colSpan; dc++)
                    setPixel(renderParams.renderTarget, row + dr, col + dc, to_pixel(color));
        }
    }

    return StatusCode::Success;
}

static bool renderViewportValid(const RectI& viewport, const RenderTarget& renderTarget)
{
    return is_valid(viewport) && is_inside(get_viewport(renderTarget), viewport);
}

static Color rayTraceRender(const Scene& scene, const Camera& camera, int pixelRow, int pixelCol)
{
    Ray ray = shoot_ray(camera, float(pixelCol), float(pixelRow));
    return traceRay(ray, scene, camera, 3).second;
}

static std::pair<double, Color> traceRay(Ray ray, const Scene& scene, const Camera& camera, int depthLeft)
{
    Mesh* mesh;
    Face* face;
    double distance;

    if (depthLeft > 0 && findIntersectionPoint(mesh, face, distance, ray, scene))
    {
        Vec position = ray_at(ray, distance);
        Vec view = normalized(position - camera.eye);
        Mat view_mat = inverse(camera.model_mat);
        // Vec normal = get_mean_normal(mesh->model_mat * *face);
        Vec normal = get_normal_at(mesh->model_mat * *face, position);

        Color colorReflected = Colors::black;
        Color colorTransmitted = Colors::black;
        Color colorLighted = Colors::black;

        if (mesh->material.coefReflection > 0)
        {
            Vec reflected = ray.direction - 2 * dot(ray.direction, normal) * normal;
            auto traced = traceRay(make_ray(position + 0.01 * reflected, reflected), scene, camera, depthLeft - 1);
            if (traced.first < std::numeric_limits<double>::infinity())
                colorReflected += mesh->material.coefReflection * traced.second;
        }
        if (mesh->material.coefRefraction > 0)
        {
            double d = dot(-ray.direction, normal);
            if (d > 0) // ray goes inside
            {
                double theta = std::acos(d); // if theta == 0...
                Vec m = (normal * std::cos(theta) + ray.direction) / std::sin(theta);
                Vec refracted = normalized(m * std::sin(theta) - normal * std::cos(theta));
                auto traced = traceRay(make_ray(position + 0.01 * refracted, refracted), scene, camera, depthLeft - 1);
                if (traced.first < std::numeric_limits<double>::infinity())
                    colorTransmitted += mesh->material.coefRefraction * traced.second;
            }
            else
            {

            }
        }

        for (size_t i = 0; i < scene.lightList.size; i++)
        {
            Light light{};

            if (!get(scene.lightList, i, light))
                return {std::numeric_limits<double>::infinity(), Colors::black};
            else if (!light.visible)
                continue;
            else
            {
                if (light.type == LightType::Ambient)
                {
                    colorLighted += light.intensity * light.color * mesh->material.ambientColor;
                }
                else if (light.type == LightType::Directional)
                {
                    //color += dot(normal, -make_dir(1, 0, 0)) * Colors::green;
                    if (dot(normal, -light.direction) > 0)
                    {
                        auto traced = traceRay(make_ray(position - 0.1 * light.direction, -light.direction), scene, camera, depthLeft - 1);
                        if (traced.first == std::numeric_limits<double>::infinity())
                        {
                            colorLighted += dot(normal, -light.direction) * light.intensity * light.color;
                        }
                    }
                }
                else if (light.type == LightType::Point)
                {
                    auto traced = traceRay(make_ray(position, normalized(light.position - position)), scene, camera, depthLeft - 1);
                    colorLighted += traced.second;
                }
            }
        }

        double op = mesh->material.opacity;
        Color color = op * colorLighted + (1 - op) * colorTransmitted + colorReflected; /// TODO: fix transparency

        return {distance, color};
        // return compute_color(mesh->material, scene.lightList, view_mat, view, normal);
    }

    Color color = Colors::black;

    for (size_t i = 0; i < scene.lightList.size; i++)
    {
        Light light{};
        get(scene.lightList, i, light);

        if (!light.visible)
            continue;
        else if (light.type == LightType::Ambient)
            color += light.intensity * light.color;
        else if (light.type == LightType::Directional)
        {
            double val = dot(ray.direction, -light.direction);
            if (val > 0)
                color += val * light.intensity * light.color;
        }
    }

    return {std::numeric_limits<double>::infinity(), color};
}

static bool findIntersectionPoint(Mesh*& mesh, Face*& face, double& distance, Ray ray, const Scene& scene)
{
    distance = std::numeric_limits<double>::infinity();
    mesh = nullptr;
    face = nullptr;

    for (auto node = scene.meshList.head; node; node = node->next)
    {
        if (!node->value.visible)
            continue;

        double t;

        Sphere bounding_sphere = get_bounding_sphere(node->value);
        if (ray_intersects(t, ray, bounding_sphere) && t < distance)
        {
            for (size_t i = 0; i < node->value.faces.size; i++)
            {
                if (ray_intersects(t, ray, node->value.model_mat * node->value.faces.data[i]) && t < distance)
                {
                    distance = t;
                    mesh = &node->value;
                    face = &mesh->faces.data[i];
                }
            }
        }
    }

    return face != nullptr;
}
