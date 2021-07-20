#include <iostream>
#include "Core.hpp"
#include "FastRender.hpp"
#include "FancyRenderer.hpp"

using namespace Core;


StatusCode Core::renderScene(RenderParams renderParams)
{
    StatusCode result = StatusCode::InvalidRenderType;

    if (renderParams.renderType == RenderParams::RenderType::FastRenderType)
    {
        // std::cout << "begin rendering..." << std::endl;
        result = fastRenderScene(renderParams);
        // std::cout << "scene rendered!" << std::endl;
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
