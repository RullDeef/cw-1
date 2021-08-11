#include "Core/OverlayRender.hpp"
#include "Core/Rasterizers/CircleRenderer.hpp"

using namespace Core;


StatusCode Core::overlayRenderScene(RenderParams renderParams)
{
    for (auto node = renderParams.scene.meshList.head; node; node = node->next)
    {
        if (node->value.wireframe)
        {
            StatusCode result = renderWireframeMesh(renderParams.renderTarget, node->value, renderParams.camera, Colors::orange, renderParams.faceCullingType);
            if (result != StatusCode::Success)
                return result;
        }
    }

    return StatusCode::Success;
}
