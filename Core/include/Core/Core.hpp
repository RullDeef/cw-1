#ifndef CORE_HPP
#define CORE_HPP

#include "Core/common/StatusCodes.hpp"
#include "Core/common/math/Rect.hpp"
#include "Core/RenderTarget/RenderTarget.hpp"
#include "Core/Objects/Camera.hpp"
#include "Core/Scene/Scene.hpp"


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
