#include "Core/Rasterizers/RenderRegion.hpp"
#include "Core/Objects/Camera.hpp"
#include "Core/Objects/Mesh.hpp"

using namespace Core;

static bool same_projected(const Vec& v1, const Vec& v2);


arr_t<RenderRegion, 2> Core::make_render_regions(const Mesh& mesh, Face face, Face projection)
{
    auto array = make_arr<RenderRegion, 2>();

    auto p1 = projection.verts[0].position;
    auto p2 = projection.verts[1].position;
    auto p3 = projection.verts[2].position;

    if (same_projected(p1, p2) || same_projected(p1, p3) || same_projected(p2, p3))
        return array; // пустой массив

    // сортировка вершин
    if (p2.y < p1.y)
    {
        std::swap(p1, p2);
        std::swap(face.verts[0], face.verts[1]);
    }
    if (p3.y < p1.y)
    {
        std::swap(p1, p3);
        std::swap(face.verts[0], face.verts[2]);
    }
    if (p3.x < p2.x)
    {
        std::swap(p2, p3);
        std::swap(face.verts[1], face.verts[2]);
    }

    // общий случай
    if (p1.y < p2.y && p1.y < p3.y)
    {
        RenderRegion region{};
        region.meshPtr = &mesh;

        region.yStart = (int)p1.y;

        region.xStartLeft = (int)p1.x;
        region.xStartRight = (int)p1.x;

        region.zStartLeft = 1.0 / (p1.z + 1.001);
        region.zStartRight = 1.0 / (p1.z + 1.001);

        region.vLeft = face.verts[0];
        region.vRight = face.verts[0];

        region.dxLeft = (p2.x - p1.x) / (p2.y - p1.y);
        region.dxRight = (p3.x - p1.x) / (p3.y - p1.y);

        region.dzLeft = (1.0 / (p2.z + 1.001) - 1.0 / (p1.z + 1.001)) / (p2.y - p1.y);
        region.dzRight = (1.0 / (p3.z + 1.001) - 1.0 / (p1.z + 1.001)) / (p3.y - p1.y);

        region.dvLeft = vertex_delta(face.verts[0], face.verts[1], p2.y - p1.y);
        region.dvRight = vertex_delta(face.verts[0], face.verts[2], p3.y - p1.y);

        if (p2.y < p3.y)
        {
            region.yEnd = (int)p2.y - 1;
            push_back(array, normalized(region));

            region.yStart = (int)p2.y;
            region.yEnd = (int)p3.y;

            region.xStartLeft = (int)p2.x;
            region.xStartRight += (int)(region.dxRight * (p2.y - p1.y));

            region.zStartLeft = 1.0 / (p2.z + 1.001);
            region.zStartRight += region.dzRight * (p2.y - p1.y);

            region.dxLeft = (p3.x - p2.x) / (p3.y - p2.y);
            region.dzLeft = (1.0 / (p3.z + 1.001) - 1.0 / (p2.z + 1.001)) / (p3.y - p2.y);

            region.vLeft = face.verts[1];
            region.vRight = interpolate(face.verts[0], face.verts[2], (p2.y - p1.y) / (p3.y - p1.y));

            region.dvLeft = vertex_delta(face.verts[1], face.verts[2], p3.y - p2.y);

            push_back(array, normalized(region));
        }
        else if (p3.y < p2.y)
        {
            region.yEnd = (int)p3.y - 1;
            push_back(array, normalized(region));

            region.yStart = (int)p3.y;
            region.yEnd = (int)p2.y;

            region.xStartLeft += (int)(region.dxLeft * (p3.y - p1.y));
            region.xStartRight = (int)p3.x;

            region.zStartLeft += region.dzLeft * (p3.y - p1.y);
            region.zStartRight = 1.0 / (p3.z + 1.001);

            region.dxRight = (p2.x - p3.x) / (p2.y - p3.y);
            region.dzRight = (1.0 / (p2.z + 1.001) - 1.0 / (p3.z + 1.001)) / (p2.y - p3.y);

            region.vLeft = interpolate(face.verts[0], face.verts[1], (p3.y - p1.y) / (p2.y - p1.y));
            region.vRight = face.verts[2];

            region.dvRight = vertex_delta(face.verts[2], face.verts[1], p2.y - p3.y);

            push_back(array, normalized(region));
        }
        else // if (p2.y == p3.y)
        {
            region.yEnd = (int)p2.y;
            push_back(array, normalized(region));
        }
    }
    else if (p1.y == p2.y)
    {
        if (p2.x < p1.x)
        {
            std::swap(p1, p2);
            std::swap(face.verts[0], face.verts[1]);
        }

        RenderRegion region{};
        region.meshPtr = &mesh;

        region.yStart = (int)p1.y;
        region.yEnd = (int)p3.y;

        region.xStartLeft = (int)p1.x;
        region.xStartRight = (int)p2.x;

        region.zStartLeft = 1.0 / (p1.z + 1.001);
        region.zStartRight = 1.0 / (p2.z + 1.001);

        region.dxLeft = (p3.x - p1.x) / (p3.y - p1.y);
        region.dxRight = (p3.x - p2.x) / (p3.y - p2.y);

        region.dzLeft = (1.0 / (p3.z + 1.001) - 1.0 / (p1.z + 1.001)) / (p3.y - p1.y);
        region.dzRight = (1.0 / (p3.z + 1.001) - 1.0 / (p2.z + 1.001)) / (p3.y - p2.y);

        region.vLeft = face.verts[0];
        region.vRight = face.verts[1];

        region.dvLeft = vertex_delta(face.verts[0], face.verts[2], p3.y - p1.y);
        region.dvRight = vertex_delta(face.verts[1], face.verts[2], p3.y - p2.y);

        push_back(array, normalized(region));
    }
    else // if (p1.y == p3.y)
    {
        if (p3.x < p1.x)
        {
            std::swap(p1, p3);
            std::swap(face.verts[0], face.verts[2]);
        }

        RenderRegion region{};
        region.meshPtr = &mesh;

        region.yStart = (int)p1.y;
        region.yEnd = (int)p2.y;

        region.xStartLeft = (int)p1.x;
        region.xStartRight = (int)p3.x;

        region.zStartLeft = 1.0 / (p1.z + 1.001);
        region.zStartRight = 1.0 / (p3.z + 1.001);

        region.dxLeft = (p2.x - p1.x) / (p2.y - p1.y);
        region.dxRight = (p2.x - p3.x) / (p2.y - p3.y);

        region.dzLeft = (1.0 / (p2.z + 1.001) - 1.0 / (p1.z + 1.001)) / (p2.y - p1.y);
        region.dzRight = (1.0 / (p2.z + 1.001) - 1.0 / (p3.z + 1.001)) / (p2.y - p3.y);

        region.vLeft = face.verts[0];
        region.vRight = face.verts[2];

        region.dvLeft = vertex_delta(face.verts[0], face.verts[1], p2.y - p1.y);
        region.dvRight = vertex_delta(face.verts[2], face.verts[1], p2.y - p3.y);

        push_back(array, normalized(region));
    }

    return array;
}

void Core::normalize(RenderRegion& region)
{
    if (region.xStartRight < region.xStartLeft
        || (region.xStartLeft == region.xStartRight && region.dxRight < region.dxLeft))
    {
        std::swap(region.xStartLeft, region.xStartRight);
        std::swap(region.zStartRight, region.zStartRight);
        std::swap(region.dxLeft, region.dxRight);
        std::swap(region.dzLeft, region.dzRight);
        std::swap(region.vLeft, region.vRight);
        std::swap(region.dvLeft, region.dvRight);
    }
}

RenderRegion Core::normalized(const RenderRegion& region)
{
    RenderRegion res = region;
    normalize(res);
    return res;
}

void Core::flat_correction(arr_t<RenderRegion, 2>& regions, const Face& face)
{
    Vec center = get_center(face);
    Vec normal = get_mean_normal(face);
    for (size_t i = 0; i < regions.size; i++)
    {
        regions.data[i].center = center;
        regions.data[i].normal = normal;
    }
}

void Core::renderFlat(RenderTarget& renderTarget, ZBuffer& zbuffer, RenderRegion region, ColorComputeFn colorComputeFn)
{
    double xLeft = region.xStartLeft;
    double xRight = region.xStartRight;

    double zLeft = region.zStartLeft;
    double zRight = region.zStartRight;

    Pixel color = to_pixel(colorComputeFn(region.center, region.normal, region.meshPtr->material));

    for (int y = region.yStart; y <= region.yEnd; y++)
    {
        double z = zLeft;
        double dz = (zRight - zLeft) / (xRight - xLeft + 1);

        if (0 <= y && y < renderTarget.height)
        {
            for (auto x = (int)xLeft; x < xRight; x++)
            {
                if (0 <= x && x < renderTarget.width)
                    updatePixel(renderTarget, zbuffer, y, x, 1.0 / z, color);

                z += dz;
            }
        }

        xLeft += region.dxLeft;
        xRight += region.dxRight;

        zLeft += region.dzLeft;
        zRight += region.dzRight;
    }
}

void Core::renderPhong(RenderTarget &renderTarget, ZBuffer &zbuffer, RenderRegion region, ColorComputeFn colorComputeFn)
{
    double xLeft = region.xStartLeft;
    double xRight = region.xStartRight;

    double zLeft = region.zStartLeft;
    double zRight = region.zStartRight;

    Vec pLeft = region.vLeft.position;
    Vec pRight = region.vRight.position;

    Vec nLeft = region.vLeft.normal;
    Vec nRight = region.vRight.normal;

    for (int y = region.yStart; y <= region.yEnd; y++)
    {
        double z = zLeft;
        double dz = (zRight - zLeft) / (xRight - xLeft + 1);

        Vec p = pLeft;
        Vec dp = (pRight - pLeft) / (xRight - xLeft + 1);

        Vec n = nLeft;
        Vec dn = (nRight - nLeft) / (xRight - xLeft + 1);

        if (0 <= y && y < renderTarget.height)
        {
            for (auto x = (int)xLeft; x < xRight; x++)
            {
                if (0 <= x && x < renderTarget.width)
                {
                    Color color = colorComputeFn(p, n, region.meshPtr->material);
                    updatePixel(renderTarget, zbuffer, y, x, 1.0 / z, to_pixel(color));
                }

                z += dz;
                n += dn;
                p += dp;
            }
        }

        xLeft += region.dxLeft;
        xRight += region.dxRight;

        zLeft += region.dzLeft;
        zRight += region.dzRight;

        pLeft += region.dvLeft.position;
        pRight += region.dvRight.position;

        nLeft += region.dvLeft.normal;
        nRight += region.dvRight.normal;
    }
}

void Core::renderGouraud(RenderTarget &renderTarget, ZBuffer &zbuffer, RenderRegion region, ColorComputeFn colorComputeFn)
{
    double xLeft = region.xStartLeft;
    double xRight = region.xStartRight;

    double zLeft = region.zStartLeft;
    double zRight = region.zStartRight;

    Vec pLeft = region.vLeft.position;
    Vec pRight = region.vRight.position;

    Vec nLeft = region.vLeft.normal;
    Vec nRight = region.vRight.normal;

    for (int y = region.yStart; y <= region.yEnd; y++)
    {
        double z = zLeft;
        double dz = (zRight - zLeft) / (xRight - xLeft + 1);

        Color cLeft = colorComputeFn(pLeft, nLeft, region.meshPtr->material);
        Color cRight = colorComputeFn(pRight, nRight, region.meshPtr->material);

        Color c = cLeft;
        Color dc = (cRight - cLeft) / (xRight - xLeft + 1);

        if (0 <= y && y < renderTarget.height)
        {
            for (auto x = (int)xLeft; x < xRight; x++)
            {
                if (0 <= x && x < renderTarget.width)
                    updatePixel(renderTarget, zbuffer, y, x, 1.0 / z, to_pixel(c));

                z += dz;
                c += dc;
            }
        }

        xLeft += region.dxLeft;
        xRight += region.dxRight;

        zLeft += region.dzLeft;
        zRight += region.dzRight;

        pLeft += region.dvLeft.position;
        pRight += region.dvRight.position;

        nLeft += region.dvLeft.normal;
        nRight += region.dvRight.normal;
    }
}

static bool same_projected(const Vec& v1, const Vec& v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}