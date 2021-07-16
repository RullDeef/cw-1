#ifndef CORE_HPP
#define CORE_HPP

#include "StatusCodes.hpp"
#include "RenderTarget.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


namespace Core
{
    enum class RenderType
    {
        FastRenderType,
        FancyRenderType
    };

    StatusCode renderScene(RenderTarget& renderTarget, const Scene& scene, const Camera& camera, RenderType renderType = RenderType::FastRenderType);
}

#endif // CORE_HPP
