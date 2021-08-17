#include "Core/RenderParams.hpp"

using namespace Core;


RenderParams Core::make_render_params(const RenderTarget& renderTarget, const Scene& scene)
{
    RenderParams params{};

    params.renderTarget = renderTarget;
    params.scene = scene;

    params.viewport = get_viewport(renderTarget);

    params.camera = make_camera();
    update_viewport(params.camera, params.viewport);

    params.renderType = RenderType::ColorFilling;
    params.sceneLightingModel = LightingModelType::Phong;
    params.faceCullingType = OcclusionCulling | BackfaceCulling;

    return params;
}

RenderParams Core::make_render_params(const RenderTarget& renderTarget, const Scene& scene, const Camera& camera)
{
    RenderParams params = make_render_params(renderTarget, scene);
    use_camera(params, camera);

    return params;
}

void Core::use_camera(RenderParams& params, const Camera& camera)
{
    params.camera = camera;
    update_viewport(params.camera, params.viewport);
}
