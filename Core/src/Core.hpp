#ifndef CORE_HPP
#define CORE_HPP

#include "StatusCodes.hpp"
#include "RenderTarget.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Rect.hpp"


namespace Core
{
    struct RenderParams
    {
        RenderTarget& renderTarget;
        const Scene& scene;
        const Camera& camera;

        enum class RenderType
        {
            FastRenderType,
            FancyRenderType
        } renderType;

        Rect viewport;
    };

    StatusCode renderScene(RenderParams renderParams);
}

#endif // CORE_HPP
