#include "Core/Rasterizers/RenderRegion.hpp"
#include "Core/Objects/Camera.hpp"
#include "Core/Objects/Mesh.hpp"

using namespace Core;

static bool same_projected(const Vec& v1, const Vec& v2);
static Pixel recomputeColor(const Vec& normal, const Vec& view, const Material& material);
static Pixel recomputeColor(const Vec& normal);


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

        region.yStart = p1.y;

        region.xStartLeft = p1.x;
        region.xStartRight = p1.x;

        region.vLeft = face.verts[0];
        region.vRight = face.verts[0];

        region.dxLeft = (p2.x - p1.x) / (p2.y - p1.y);
        region.dxRight = (p3.x - p1.x) / (p3.y - p1.y);

        region.dvLeft = vertex_delta(face.verts[0], face.verts[1], p2.y - p1.y);
        region.dvRight = vertex_delta(face.verts[0], face.verts[2], p3.y - p1.y);

        if (p2.y < p3.y)
        {
            region.yEnd = p2.y - 1;
            push_back(array, normalized(region));

            region.yStart = p2.y;
            region.yEnd = p3.y;

            region.xStartLeft = p2.x;
            region.xStartRight += region.dxRight * (p2.y - p1.y);

            region.dxLeft = (p3.x - p2.x) / (p3.y - p2.y);

            region.vLeft = face.verts[1];
            region.vRight = interpolate(face.verts[0], face.verts[2], (p2.y - p1.y) / (p3.y - p1.y));

            region.dvLeft = vertex_delta(face.verts[1], face.verts[2], p3.y - p2.y);

            push_back(array, normalized(region));
        }
        else if (p3.y < p2.y)
        {
            region.yEnd = p3.y - 1;
            push_back(array, normalized(region));

            region.yStart = p3.y;
            region.yEnd = p2.y;

            region.xStartLeft += region.dxLeft * (p3.y - p1.y);
            region.xStartRight = p3.x;

            region.dxRight = (p2.x - p3.x) / (p2.y - p3.y);

            region.vLeft = interpolate(face.verts[0], face.verts[1], (p3.y - p1.y) / (p2.y - p1.y));
            region.vRight = face.verts[2];

            region.dvRight = vertex_delta(face.verts[2], face.verts[1], p2.y - p3.y);

            push_back(array, normalized(region));
        }
        else // if (p2.y == p3.y)
        {
            region.yEnd = p2.y;
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

        region.yStart = p1.y;
        region.yEnd = p3.y;

        region.xStartLeft = p1.x;
        region.xStartRight = p2.x;

        region.dxLeft = (p3.x - p1.x) / (p3.y - p1.y);
        region.dxRight = (p3.x - p2.x) / (p3.y - p2.y);

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

        region.yStart = p1.y;
        region.yEnd = p2.y;

        region.xStartLeft = p1.x;
        region.xStartRight = p3.x;

        region.dxLeft = (p2.x - p1.x) / (p2.y - p1.y);
        region.dxRight = (p2.x - p3.x) / (p2.y - p3.y);

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
        std::swap(region.dxLeft, region.dxRight);
        std::swap(region.nLeft, region.nRight);
        std::swap(region.dnLeft, region.dnRight);
    }
}

RenderRegion Core::normalized(const RenderRegion& region)
{
    RenderRegion res = region;
    normalize(res);
    return res;
}

void Core::render(RenderTarget &renderTarget, ZBuffer &zbuffer, RenderRegion region, const Camera& camera)
{
    double xLeft = std::max(0u, region.xStartLeft);
    double xRight = std::min(region.xStartRight, (unsigned int)renderTarget.width);

    Vec pLeft = region.vLeft.position;
    Vec pRight = region.vRight.position;

    Vec nLeft = region.vLeft.normal;
    Vec nRight = region.vRight.normal;

    for (unsigned int y = region.yStart; y <= region.yEnd; y++)
    {
        Vec p = pLeft;
        Vec dp = (pRight - pLeft) / (xRight - xLeft + 1);

        Vec n = nLeft;
        Vec dn = (nRight - nLeft) / (xRight - xLeft + 1);

        for (auto x = (unsigned int)xLeft; x < xRight + 1; x++)
        {
            Vec view = normalised(p - camera.eye);

            Pixel color = recomputeColor(normalised(n), view, region.meshPtr->material);
            updatePixel(renderTarget, zbuffer, y, x, 0.0, color);
            n += dn;
            p += dp;
        }

        xLeft += region.dxLeft;
        xRight += region.dxRight;

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

static Pixel recomputeColor(const Vec& normal)
{
    static Vec light_1 = normalised(make_dir(-1, 2, 1));
    static Vec light_2 = normalised(make_dir(3, 4, -2));

    double lit_factor_1 = dot(normal, light_1);
    double lit_factor_2 = dot(normal, light_2);
    if (lit_factor_1 < 0) lit_factor_1 = 0;
    if (lit_factor_2 < 0) lit_factor_2 = 0;

    Pixel color{};
    { // generate color from lit factor
        const int min_r = 64;
        const int max_r = 255;
        const int min_g = 64;
        const int max_g = 255;
        const int min_b = 64;
        const int max_b = 255;

        color.red   = min_r + (max_r - min_r) * (0.75 * lit_factor_1 + 0.25 * lit_factor_2);
        color.green = min_g + (max_g - min_g) * (0.50 * lit_factor_1 + 0.50 * lit_factor_2);
        color.blue  = min_b + (max_b - min_b) * (0.25 * lit_factor_1 + 0.75 * lit_factor_2);
        color.alpha = 255;
    }

    return color;
}

static Pixel recomputeColor(const Vec& normal, const Vec& view, const Material& material)
{
    static Vec light_1 = normalised(make_dir(-1, 2, 1));
    static Vec light_2 = normalised(make_dir(3, 4, -2));

    auto lights = make_arr<Vec, 2>();
    push_back(lights, light_1);
    push_back(lights, light_2);

    Color color = compute_color(material, lights, view, normal);
    return to_pixel(color);
}
