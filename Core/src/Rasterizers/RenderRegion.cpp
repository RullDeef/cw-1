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

        region.yStart = (int)p1.y;

        region.xStartLeft = (int)p1.x;
        region.xStartRight = (int)p1.x;

        region.zStartLeft = p1.z;
        region.zStartRight = p1.z;

        region.vLeft = face.verts[0];
        region.vRight = face.verts[0];

        region.dxLeft = (p2.x - p1.x) / (p2.y - p1.y);
        region.dxRight = (p3.x - p1.x) / (p3.y - p1.y);

        region.dzLeft = (p2.z - p1.z) / (p2.y - p1.y);
        region.dzRight = (p3.z - p1.z) / (p3.y - p1.y);

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

            region.zStartLeft = p2.z;
            region.zStartRight += region.dzRight * (p2.z - p1.z);

            region.dxLeft = (p3.x - p2.x) / (p3.y - p2.y);
            region.dzLeft = (p3.z - p2.z) / (p3.y - p2.y);

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
            region.zStartRight = p3.z;

            region.dxRight = (p2.x - p3.x) / (p2.y - p3.y);
            region.dzRight = (p2.z - p3.z) / (p2.y - p3.y);

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

        region.zStartLeft = p1.z;
        region.zStartRight = p2.z;

        region.dxLeft = (p3.x - p1.x) / (p3.y - p1.y);
        region.dxRight = (p3.x - p2.x) / (p3.y - p2.y);

        region.dzLeft = (p3.z - p1.z) / (p3.y - p1.y);
        region.dzRight = (p3.z - p2.z) / (p3.y - p2.y);

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

        region.zStartLeft = p1.z;
        region.zStartRight = p3.z;

        region.dxLeft = (p2.x - p1.x) / (p2.y - p1.y);
        region.dxRight = (p2.x - p3.x) / (p2.y - p3.y);

        region.dzLeft = (p2.z - p1.z) / (p2.y - p1.y);
        region.dzRight = (p2.z - p3.z) / (p2.y - p3.y);

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

void Core::render(RenderTarget &renderTarget, ZBuffer &zbuffer, RenderRegion region, const Camera& camera)
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
            for (auto x = (int)xLeft; x < xRight + 1; x++)
            {
                if (0 <= x && x < renderTarget.width)
                {
                    Vec view = normalized(p - camera.eye);

                    Pixel color = recomputeColor(normalized(n), view, region.meshPtr->material);
                    updatePixel(renderTarget, zbuffer, y, x, z, color);
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

static bool same_projected(const Vec& v1, const Vec& v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

static Pixel recomputeColor(const Vec& normal)
{
    static Vec light_1 = normalized(make_dir(-1, 2, 1));
    static Vec light_2 = normalized(make_dir(3, 4, -2));

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
    /// TODO: microfix for testing
    return recomputeColor(normal);

    static Light light_0 = { Light::Type::Ambient };
    light_0.ambient = {
            make_color(1.0, 0.0, 0.0),
            0.3
    };
    static Light light_1 = { Light::Type::Directional };
    light_1.directional = (DirectionalLight) {
            make_color(0.0, 1.0, 0.0),
            0.4,
            normalized(make_dir(0.2, 0.4, -0.8))
    };
    static Light light_2 = { Light::Type::Directional };
    light_2.directional = (DirectionalLight) {
            make_color(0.0, 0.0, 1.0),
            0.4,
            normalized(make_dir(3, 4, -2))
    };

    auto lights = make_arr<Light, 3>();
    push_back(lights, light_0);
    push_back(lights, light_1);
    push_back(lights, light_2);

    Color color = compute_color(material, lights, view, normal);
    return to_pixel(color);
}
