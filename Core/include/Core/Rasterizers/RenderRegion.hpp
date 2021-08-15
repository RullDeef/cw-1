#ifndef RENDERREGION_HPP
#define RENDERREGION_HPP

#include "Core/containers/arr_t.hpp"
#include "Core/math/Vec.hpp"
#include "Core/RenderTarget/RenderTarget.hpp"
#include "Core/RenderTarget/ZBuffer.hpp"
#include "Core/Objects/Face.hpp"


namespace Core
{
    struct Mesh;
    struct Camera;

    struct RenderRegion
    {
        int yStart;
        int yEnd;

        int xStartLeft;
        int xStartRight;

        double zStartLeft;
        double zStartRight;

        double dxLeft;
        double dxRight;

        double dzLeft;
        double dzRight;

        Vertex vLeft;
        Vertex vRight;

        Vertex dvLeft;
        Vertex dvRight;

        // used in flat rendering
        Vec center;
        Vec normal;

        const Mesh* meshPtr;
    };

    // создаёт одну или две области для отображения из полигона и его проекции
    arr_t<RenderRegion, 2> make_render_regions(const Mesh& mesh, Face face, Face projection);

    // для плоской модели освещения
    arr_t<RenderRegion, 2> make_flat_render_regions(const Mesh& mesh, Face face, Face projection);

    // меняет местами левый и правый конец при необходимости
    void normalize(RenderRegion& region);
    RenderRegion normalized(const RenderRegion& region);

    void flat_correction(arr_t<RenderRegion, 2>& regions, const Face& face);

    void renderFlat(RenderTarget& renderTarget, ZBuffer& zbuffer, RenderRegion region, ColorComputeFn colorComputeFn);
    void renderPhong(RenderTarget& renderTarget, ZBuffer& zbuffer, RenderRegion region, ColorComputeFn colorComputeFn);
    void renderGouraud(RenderTarget& renderTarget, ZBuffer& zbuffer, RenderRegion region, ColorComputeFn colorComputeFn);
}

#endif // RENDERREGION_HPP
