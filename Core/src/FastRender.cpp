#include "Core/Rasterizers/RenderRegion.hpp"
#include "Core/Rasterizers/LineRenderer.hpp"
#include "Core/FastRender.hpp"
#include "Core/Objects/Material.hpp"

using namespace Core;

static ColorComputeFn makeColorComputator(Camera camera, vect_t<Light> lights);


StatusCode Core::fastRenderScene(RenderParams renderParams)
{
    ZBuffer zbuffer = make_zbuffer(renderParams.renderTarget.width, renderParams.renderTarget.height);
    fill(zbuffer, 1000000);

    fill(renderParams.renderTarget, to_pixel(Colors::black));

    ColorComputeFn colorComputor = makeColorComputator(renderParams.camera, renderParams.scene.lightList);

    for (list_node<Mesh>* node = renderParams.scene.meshList.head; node; node = node->next)
        if (node->value.visible)
            renderMesh(renderParams.renderTarget, zbuffer, node->value, renderParams.camera, renderParams.sceneLightingModel, renderParams.faceCullingType, colorComputor);

    destroy(zbuffer);
    return StatusCode::Success;
}

ColorComputeFn makeColorComputator(Camera camera, vect_t<Light> lights)
{
    return [camera, lights](const Vec& position, const Vec& normal, const Material& material) -> Color
    {
        Vec view = normalized(position - camera.eye);
        return compute_color(material, lights, view, normal);
    };
}
