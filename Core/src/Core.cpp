#include <iostream>
#include "Core/Core.hpp"
#include "Core/FastRender.hpp"
#include "Core/FancyRenderer.hpp"

using namespace Core;


StatusCode Core::renderScene(RenderParams renderParams)
{
    StatusCode result = StatusCode::InvalidRenderType;

    if (renderParams.renderType == RenderParams::RenderType::FastRenderType)
    {
        result = fastRenderScene(renderParams);
    }
    else if (renderParams.renderType == RenderParams::RenderType::FancyRenderType)
    {
        result = fancyRenderScene(renderParams);
    }
    else
    {
        std::cout << "not implemented rendering type: " << (int)renderParams.renderType << std::endl;
    }

    return result;
}
