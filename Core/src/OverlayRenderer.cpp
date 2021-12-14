#include "Core/OverlayRender.hpp"
#include "Core/Rasterizers/CircleRenderer.hpp"
#include "Core/Rasterizers/LineRenderer.hpp"

using namespace Core;

const Color wireframeColor = Colors::orange;

const double orientationBoxSize = 32.0; // px
static StatusCode renderOrientationBox(RenderTarget& renderTarget, const Mat& viewMat, int offsetX, int offsetY);
static StatusCode renderOrientationBoxSide(RenderTarget& renderTarget, Vec normal, const Vec& tangent, Color color, int offsetX, int offsetY);


StatusCode Core::overlayRenderScene(RenderParams renderParams)
{
    fill(renderParams.renderTarget, to_pixel(Colors::transparent));

    for (auto node = renderParams.scene.meshList.head; node; node = node->next)
    {
        StatusCode result = renderWireframeMesh(renderParams.renderTarget,
            node->value, renderParams.camera, wireframeColor, renderParams.faceCullingType);
        if (result != StatusCode::Success)
            return result;
    }

    recalc_mvp(renderParams.camera, make_mat_id());
    for (size_t i = 0; i < renderParams.scene.lightList.size; i++)
    {
        Light light{};
        if (get(renderParams.scene.lightList, i, light))
        {
            Vec pos = project_point(renderParams.camera, light.position);
            if (light.outline && std::abs(pos.z) < std::abs(pos.w))
            {
                int x = int(pos.x), y = int(pos.y), r = 10; /// TODO: magic constant - 10
                renderCircle(renderParams.renderTarget, x, y, r, Colors::light_cyan);
            }
        }
    }

    /// TODO: fix wrong rotations (maybe done)
//    recalc_mvp(renderParams.camera, make_mat_id());
//    renderOrientationBox(renderParams.renderTarget, renderParams.camera.mvp, 20, 20);

    return StatusCode::Success;
}

static StatusCode renderOrientationBox(RenderTarget& renderTarget, const Mat& viewMat, int offsetX, int offsetY)
{
    Vec dirX = viewMat * make_dir(1, 0, 0);
    Vec dirY = viewMat * make_dir(0, 1, 0);
    Vec dirZ = viewMat * make_dir(0, 0, 1);

    if (dirX.z < 0.0)
        renderOrientationBoxSide(renderTarget, dirX, dirY, Colors::red, offsetX, offsetY);
    else
        renderOrientationBoxSide(renderTarget, -dirX, -dirY, Colors::red, offsetX, offsetY);

    if (dirY.z < 0.0)
        renderOrientationBoxSide(renderTarget, dirY, dirZ, Colors::green, offsetX, offsetY);
    else
        renderOrientationBoxSide(renderTarget, -dirY, -dirZ, Colors::green, offsetX, offsetY);

    if (dirZ.z < 0.0)
        renderOrientationBoxSide(renderTarget, dirZ, dirX, Colors::blue, offsetX, offsetY);
    else
        renderOrientationBoxSide(renderTarget, -dirZ, -dirX, Colors::blue, offsetX, offsetY);

    return StatusCode::Success;
}

static StatusCode renderOrientationBoxSide(RenderTarget& renderTarget, Vec normal, const Vec& tangent, Color color, int offsetX, int offsetY)
{
    double centerX = renderTarget.width - offsetX - orientationBoxSize / 2.0;
    double centerY = 0;
    Vec center = make_pos(centerX, centerY, 0);

    // normal.y *= -1;

    Vec point = center + (orientationBoxSize / 2.0 + 2.0) * normal;
    Vec tan2 = cross(normal, tangent);

    Vec p1 = point + orientationBoxSize / 2.0 * tangent + orientationBoxSize / 2.0 * tan2;
    Vec p2 = point + orientationBoxSize / 2.0 * tangent - orientationBoxSize / 2.0 * tan2;
    Vec p3 = point - orientationBoxSize / 2.0 * tangent - orientationBoxSize / 2.0 * tan2;
    Vec p4 = point - orientationBoxSize / 2.0 * tangent + orientationBoxSize / 2.0 * tan2;

    p1.y = offsetY + orientationBoxSize / 2.0 - p1.y;
    p2.y = offsetY + orientationBoxSize / 2.0 - p2.y;
    p3.y = offsetY + orientationBoxSize / 2.0 - p3.y;
    p4.y = offsetY + orientationBoxSize / 2.0 - p4.y;

    renderLine(renderTarget, p1, p2, to_pixel(color));
    renderLine(renderTarget, p2, p3, to_pixel(color));
    renderLine(renderTarget, p3, p4, to_pixel(color));
    renderLine(renderTarget, p4, p1, to_pixel(color));

    return StatusCode::Success;
}
