#include "Core/Rasterizers/RenderRegion.hpp"
#include "Core/Rasterizers/LineRenderer.hpp"
#include "Core/FastRender.hpp"
#include "Core/Objects/Material.hpp"

using namespace Core;

static ColorComputeFn makeColorComputator(Camera camera, vect_t<Light> lights);
static ColorComputeFn makeShadedColorComputator(Scene scene, Camera camera);

static void renderTestCube(RenderTarget& renderTarget, Camera& camera);

StatusCode Core::fastRenderScene(RenderParams renderParams)
{
    ZBuffer zbuffer = make_zbuffer(renderParams.renderTarget.width, renderParams.renderTarget.height);
    fill(zbuffer, std::numeric_limits<double>::max());

    fill(renderParams.renderTarget, to_pixel(Colors::black));

    ColorComputeFn colorComputator =
            // makeShadedColorComputator(renderParams.scene, renderParams.camera);
            makeColorComputator(renderParams.camera, renderParams.scene.lightList);

    StatusCode status = StatusCode::Success;
    for (list_node<Mesh>* node = renderParams.scene.meshList.head; node && status == StatusCode::Success; node = node->next)
        status = renderMesh(renderParams.renderTarget, zbuffer, node->value, renderParams.camera,
            renderParams.sceneLightingModel, renderParams.faceCullingType, colorComputator);

    // renderTestCube(renderParams.renderTarget, renderParams.camera);

    destroy(zbuffer);
    return status;
}

static void __renderCubeSide(RenderTarget& renderTarget, Camera& camera, Vec p1, Vec p2, Vec p3, Vec p4, Color color)
{
    p1 = project_point(camera, p1);
    p2 = project_point(camera, p2);
    p3 = project_point(camera, p3);
    p4 = project_point(camera, p4);

    renderLine(renderTarget, p1, p2, to_pixel(color));
    renderLine(renderTarget, p2, p3, to_pixel(color));
    renderLine(renderTarget, p3, p4, to_pixel(color));
    renderLine(renderTarget, p4, p1, to_pixel(color));
}

static void renderTestCube(RenderTarget& renderTarget, Camera& camera)
{
    double cube_side = 100.0, k = 1.1;
    Vec p1, p2, p3, p4;

    recalc_mvp(camera, make_mat_id());

    p1 = make_pos(k * cube_side, -cube_side, -cube_side);
    p2 = make_pos(k * cube_side, -cube_side,  cube_side);
    p3 = make_pos(k * cube_side,  cube_side,  cube_side);
    p4 = make_pos(k * cube_side,  cube_side, -cube_side);
    __renderCubeSide(renderTarget, camera, p1, p2, p3, p4, Colors::orange);

    p1 = make_pos(-cube_side, k * cube_side, -cube_side);
    p2 = make_pos(-cube_side, k * cube_side,  cube_side);
    p3 = make_pos( cube_side, k * cube_side,  cube_side);
    p4 = make_pos( cube_side, k * cube_side, -cube_side);
    __renderCubeSide(renderTarget, camera, p1, p2, p3, p4, Colors::green);

    p1 = make_pos(-cube_side, -cube_side, k * cube_side);
    p2 = make_pos(-cube_side,  cube_side, k * cube_side);
    p3 = make_pos( cube_side,  cube_side, k * cube_side);
    p4 = make_pos( cube_side, -cube_side, k * cube_side);
    __renderCubeSide(renderTarget, camera, p1, p2, p3, p4, Colors::blue);

    cube_side *= 0.5;
    p1 = make_pos(-k * cube_side, -cube_side, -cube_side);
    p2 = make_pos(-k * cube_side, -cube_side,  cube_side);
    p3 = make_pos(-k * cube_side,  cube_side,  cube_side);
    p4 = make_pos(-k * cube_side,  cube_side, -cube_side);
    __renderCubeSide(renderTarget, camera, p1, p2, p3, p4, Colors::orange);

    p1 = make_pos(-cube_side, -k * cube_side, -cube_side);
    p2 = make_pos(-cube_side, -k * cube_side,  cube_side);
    p3 = make_pos( cube_side, -k * cube_side,  cube_side);
    p4 = make_pos( cube_side, -k * cube_side, -cube_side);
    __renderCubeSide(renderTarget, camera, p1, p2, p3, p4, Colors::green);

    p1 = make_pos(-cube_side, -cube_side, -k * cube_side);
    p2 = make_pos(-cube_side,  cube_side, -k * cube_side);
    p3 = make_pos( cube_side,  cube_side, -k * cube_side);
    p4 = make_pos( cube_side, -cube_side, -k * cube_side);
    __renderCubeSide(renderTarget, camera, p1, p2, p3, p4, Colors::blue);
}

ColorComputeFn makeColorComputator(Camera camera, vect_t<Light> lights)
{
    /**
     * position - real point position in world coordinate system
     * normal - real, not rotated normal vector to mesh surface in given point
     */
    return [camera, lights](const Vec& position, const Vec& normal, const Material& material) -> Color
    {
        Vec view = normalized(position - camera.eye);
        return compute_color(material, lights, position, view, normal);
    };
}

static ColorComputeFn makeShadedColorComputator(Scene scene, Camera camera)
{
    return [scene, camera](const Vec& position, const Vec& normal, const Material& material) -> Color
    {
        //double dist = length(position - camera.eye);
        //return Colors::light_cyan * (0.8 + 0.2 * std::sin(dist / 10.0));

        Vec view = normalized(position - camera.eye);
        return compute_color(material, scene, scene.lightList, position, view, normal);
    };
}
