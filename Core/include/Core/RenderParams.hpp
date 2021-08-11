#ifndef RENDERPARAMS_HPP
#define RENDERPARAMS_HPP

#include "Core/math/Rect.hpp"
#include "Core/RenderTarget/RenderTarget.hpp"
#include "Core/Objects/Camera.hpp"
#include "Core/Scene/Scene.hpp"


namespace Core
{
    enum struct RenderType
    {
        Fast,
        Fancy,
        Overlay
    };

    enum struct LightingModelType
    {
        Flat,
        Gouraud,
        Phong
    };

    struct RenderParams
    {
        RenderTarget renderTarget;
        Scene scene;
        Camera camera;

        Rect viewport; // describes portion of render target

        RenderType renderType;
        LightingModelType sceneLightingModel;

        FaceCullingType faceCullingType;
    };

    RenderParams make_render_params(const RenderTarget& renderTarget, const Scene& scene);
    RenderParams make_render_params(const RenderTarget& renderTarget, const Scene& scene, const Camera& camera);

    void use_camera(RenderParams& params, const Camera& camera);
}

#endif // RENDERPARAMS_HPP
