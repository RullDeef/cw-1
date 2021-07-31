#ifndef RENDERREGION_HPP
#define RENDERREGION_HPP

#include "Core/common/containers/arr_t.hpp"
#include "Core/common/math/Vec.hpp"
#include "Core/RenderTarget/RenderTarget.hpp"
#include "Core/RenderTarget/ZBuffer.hpp"
#include "Core/Objects/Face.hpp"


namespace Core
{
    struct Mesh;
    struct Camera;

    struct RenderRegion
    {
        unsigned int yStart;
        unsigned int yEnd;

        unsigned int xStartLeft;
        unsigned int xStartRight;

        double dxLeft;
        double dxRight;

        Vertex vLeft;
        Vertex vRight;

        Vertex dvLeft;
        Vertex dvRight;

        Vec nLeft;
        Vec nRight;

        Vec dnLeft;
        Vec dnRight;

        const Mesh* meshPtr;
    };

    // создаёт одну или две области для отображения из полигона и его проекции
    arr_t<RenderRegion, 2> make_render_regions(const Mesh& mesh, Face face, Face projection);

    // меняет местами левый и правый конец при необходимости
    void normalize(RenderRegion& region);
    RenderRegion normalized(const RenderRegion& region);

    void render(RenderTarget& renderTarget, ZBuffer& zbuffer, RenderRegion region, const Camera& camera);
}

#endif // RENDERREGION_HPP
