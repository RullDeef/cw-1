#include <iostream>
#include "Core.hpp"
#include "FastRender.hpp"

using namespace Core;


StatusCode Core::renderScene(RenderTarget& renderTarget, const Scene& scene, const Camera& camera, RenderType renderType)
{
    StatusCode result = StatusCode::InvalidRenderType;

    if (renderType == RenderType::FastRenderType)
    {
        // std::cout << "begin rendering..." << std::endl;
        result = fastRenderScene(renderTarget, scene, camera);
        // std::cout << "scene rendered!" << std::endl;
    }
    else
    {
        std::cout << "not implemented rendering type: " << (int)renderType << std::endl;
    }

    return result;
}
