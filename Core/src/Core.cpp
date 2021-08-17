#include <iostream>
#include "Core/OverlayRender.hpp"
#include "Core/Core.hpp"
#include "Core/FastRender.hpp"
#include "Core/FancyRenderer.hpp"

using namespace Core;


StatusCode Core::renderScene(RenderParams renderParams)
{
    StatusCode result = StatusCode::InvalidRenderType;

    if (renderParams.renderType == RenderType::ColorFilling)
    {
        result = fastRenderScene(renderParams);
    }
    else if (renderParams.renderType == RenderType::RayTracing)
    {
        result = fancyRenderScene(renderParams);
    }
    else if (renderParams.renderType == RenderType::Overlay)
    {
        result = overlayRenderScene(renderParams);
    }
    else
    {
        std::cout << "not implemented rendering type: " << (int)renderParams.renderType << std::endl;
    }

    return result;
}
