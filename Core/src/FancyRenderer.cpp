#include <cmath>
#include "Core/common/math/Ray.hpp"
#include "Core/common/math/Plane.hpp"
#include "Core/Objects/Mesh.hpp"
#include "Core/Rasterizers/RectRenderer.hpp"
#include "Core/FancyRenderer.hpp"

using namespace Core;

static bool renderViewportValid(const Rect& viewport, const RenderTarget& renderTarget);
static void rayTraceRender(RenderTarget& renderTarget, const Scene& scene, const Camera& camera, int pixelRow, int pixelCol);
static Ray initRay(const Camera& camera, int pixelRow, int pixelCol);


StatusCode Core::fancyRenderScene(RenderParams renderParams)
{
    // check rendering viewport
    if (!renderViewportValid(renderParams.viewport, renderParams.renderTarget))
        return StatusCode::InvalidRenderViewport;

    for (int row = renderParams.viewport.top; row < renderParams.viewport.top + renderParams.viewport.height; row++)
    {
        for (int col = renderParams.viewport.left; col < renderParams.viewport.left + renderParams.viewport.width; col++)
        {
            rayTraceRender(renderParams.renderTarget, renderParams.scene, renderParams.camera, row, col);
        }
    }

    renderRect(renderParams.renderTarget, renderParams.viewport, to_pixel(Colors::black));

    return StatusCode::Success;
}

static bool renderViewportValid(const Rect& viewport, const RenderTarget& renderTarget)
{
    return is_valid(viewport)
        && viewport.top + viewport.height <= renderTarget.height
        && viewport.left + viewport.width <= renderTarget.width;
}

static void rayTraceRender(RenderTarget& renderTarget, const Scene& scene, const Camera& camera, int pixelRow, int pixelCol)
{
    double distance = 0.0;

    //Vec cameraPos = camera.model_mat * make_pos(0, 0, 0);
    //Vec startDir = inverse(camera.model_mat) * make_pos(pixelCol, pixelRow, 1) - cameraPos;
    //Ray ray = make_ray(cameraPos, startDir);

    Ray ray = initRay(camera, pixelRow, pixelCol);

    double closest_t = std::numeric_limits<double>::infinity();
    size_t closest_i = -1;
    list_node<Mesh>* closest_mesh = nullptr;

    /// test ray to plane
//    if (0) {
//        Vec pos = make_pos(0, 0, -1);
//        Vec dir = normalized(make_dir(1, 1, 1));
//        Ray ray = make_ray(pos, dir);
//
//        Plane plane = make_plane(-1, -1, 0, 4);
//        double t;
//        bool i = ray_intersects(t, ray, plane);
//    }

    /// test ray to triangle
//    if (0) {
//        Vec pos = make_pos(0, 0, 0);
//        Vec dir = normalized(make_dir(1, 1, 1));
//        Ray ray = make_ray(pos, dir);
//
//        Face face{};
//        face.verts[0].position = make_pos(1, 0, 0);
//        face.verts[1].position = make_pos(0, 1, 0);
//        face.verts[2].position = make_pos(0, 0, 1);
//
//        double t;
//        bool i = ray_intersects(t, ray, face);
//
//        t = 0.0;
//    }

    // cast ray to first closest intersection
    for (auto meshNode = scene.meshList.head; meshNode; meshNode = meshNode->next)
    {
        auto& faces = meshNode->value.faces;

        for (size_t i = 0; i < faces.size; i++)
        {
            double t;
            if (ray_intersects(t, ray, faces.data[i]))
            {
                if (t < closest_t)
                {
                    closest_t = t;
                    closest_i = i;
                    closest_mesh = meshNode;
                }
            }
        }
    }

    if (closest_i < size_t(-1))
    {
        distance = length(ray_at(ray, closest_t) - ray.position);

        Pixel color = to_pixel(Colors::white);

        color.red = 255 * (0.5 + 0.5 * std::sin(distance / 5));
        color.green = 255 * (0.5 + 0.5 * std::sin(distance / 5));
        color.blue = 255 * (0.5 + 0.5 * std::sin(distance / 5));

        setPixel(renderTarget, pixelRow, pixelCol, color);
    }
    else
        setPixel(renderTarget, pixelRow, pixelCol, to_pixel(Colors::black));
}

static Ray initRay(const Camera& camera, int pixelRow, int pixelCol)
{
    Vec position = camera.model_mat * make_pos(0, 0, 0);
    Vec direction = make_dir(0, 0, 0);

    direction.x = pixelCol - (camera.viewport.left + camera.viewport.width / 2);
    direction.y = (camera.viewport.top + camera.viewport.height / 2) - pixelRow;
    direction.z = std::min(camera.viewport.width, camera.viewport.height) / std::tan(camera.fov);

    normalize(direction);
    return make_ray(position, direction);
}
