#include <iostream>
#include "Core/Core.hpp"
#include "Core/FastRender.hpp"
#include "Core/FancyRenderer.hpp"

using namespace Core;


StatusCode Core::renderScene(RenderParams renderParams)
{
    StatusCode result = StatusCode::InvalidRenderType;

    if (renderParams.renderType == RenderType::Fast)
    {
        result = fastRenderScene(renderParams);
    }
    else if (renderParams.renderType == RenderType::Fancy)
    {
        result = fancyRenderScene(renderParams);
    }
    else
    {
        fill(renderParams.renderTarget, to_pixel(Colors::transparent));
        std::cout << "not implemented rendering type: " << (int)renderParams.renderType << std::endl;
    }

    return result;
}
