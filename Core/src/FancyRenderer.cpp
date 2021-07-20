#include "FancyRenderer.hpp"

using namespace Core;

static bool renderViewportValid(const Rect& viewport, const RenderTarget& renderTarget);
static void rayTraceRender(RenderTarget& renderTarget, const Scene& scene, const Camera& camera, int pixelRow, int pixelCol);


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

    setPixel(renderTarget, pixelRow, pixelCol, Color::blue);
}

