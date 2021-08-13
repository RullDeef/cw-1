#include "Core/OverlayRender.hpp"
#include "Core/Rasterizers/CircleRenderer.hpp"

using namespace Core;

const Color wireframeColor = Colors::orange;


StatusCode Core::overlayRenderScene(RenderParams renderParams)
{
    fill(renderParams.renderTarget, to_pixel(Colors::transparent));

    for (auto node = renderParams.scene.meshList.head; node; node = node->next)
    {
        if (node->value.wireframe)
        {
            StatusCode result = renderWireframeMesh(renderParams.renderTarget, node->value, renderParams.camera,
                                                    wireframeColor, renderParams.faceCullingType);
            if (result != StatusCode::Success)
                return result;
        }
    }

    recalc_mvp(renderParams.camera, make_mat_id());
    for (size_t i = 0; i < renderParams.scene.lightList.size; i++)
    {
        Light light{};
        if (get(renderParams.scene.lightList, i, light))
        {
            Vec pos = project_point(renderParams.camera, light.position);
            int x = pos.x, y = pos.y, r = 10;
            renderCircle(renderParams.renderTarget, x, y, r, Colors::light_cyan);
        }
    }

    return StatusCode::Success;
}
