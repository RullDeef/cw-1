#include "Core/FastRender.hpp"
#include "Core/Rasterizers/LineRenderer.hpp"
#include "Core/RenderTarget/ZBuffer.hpp"
#include "Core/common/math/Mat.hpp"
#include "Core/common/math/Plane.hpp"

using namespace Core;

static void makeBG(RenderTarget& renderTarget);
static StatusCode renderWireframeMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, const Camera& camera);
static StatusCode renderFace(RenderTarget& renderTarget, ZBuffer& zbuffer, Face face, const Camera& camera);
static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2, Pixel color = Color::green);
static bool backFaceCooling(const Face& face, const Camera& camera);
static bool oculusCooling(const Face& face, const Camera& camera);
static bool same_projected(const Vec& v1, const Vec& v2);

// clipping functions
static Vec projectToFrustrum(const Camera& camera, const Vec& point);
static unsigned int computeBitCode(const Vec& point);

static Pixel recomputeColor(const Vec& normal);


StatusCode Core::fastRenderScene(RenderParams renderParams)
{
    ZBuffer zbuffer = make_zbuffer(renderParams.renderTarget.width, renderParams.renderTarget.height);
    fill(zbuffer, 1000000);

    makeBG(renderParams.renderTarget);

    for (auto node = renderParams.scene.meshList.head; node; node = node->next)
        renderWireframeMesh(renderParams.renderTarget, zbuffer, node->value, renderParams.camera);

    destroy(zbuffer);
    return StatusCode::Success;
}

static void makeBG(RenderTarget& renderTarget)
{
    for (size_t row = 0; row < renderTarget.height; row++)
    {
        for (size_t col = 0; col < renderTarget.width; col++)
        {
            if (true || ((row / 64) % 2 == 0) ^ ((col / 64) % 2 == 0))
                setPixel(renderTarget, row, col, Color::black);
            else
                setPixel(renderTarget, row, col, { 64u, 0u, 64u, 255u });
        }
    }
}

static StatusCode renderWireframeMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, const Camera& camera)
{
    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);
        renderFace(renderTarget, zbuffer, *face, camera);
    }

    return StatusCode::Success;
}

static StatusCode renderFace(RenderTarget& renderTarget, ZBuffer& zbuffer, Face face, const Camera& camera)
{
    if (oculusCooling(face, camera) || backFaceCooling(face, camera))
        return StatusCode::Success;

    Vec p1 = project_point(camera, face.verts[0].position);
    p1.x = int(p1.x); p1.y = int(p1.y);
    Vec p2 = project_point(camera, face.verts[1].position);
    p2.x = int(p2.x); p2.y = int(p2.y);
    Vec p3 = project_point(camera, face.verts[2].position);
    p3.x = int(p3.x); p3.y = int(p3.y);

    // check if two points maps to the same point
    if (same_projected(p1, p2) || same_projected(p1, p3) || same_projected(p2, p3))
        return StatusCode::Success;

    Pixel color = Color::black;
    Vec n{};
    if (1) {
        n = face.verts[0].normal;

        Vec light = - (face.verts[0].position + face.verts[1].position + face.verts[2].position) / 3.0 + view_pos(camera); // -view_dir(camera); // make_dir(-1, 2, 1);
        normalise(light);

        double lit_factor = dot(n, light);
        if (lit_factor < 0) lit_factor = 0;

        { // generate color from lit factor
            const int min_r = 64;
            const int max_r = 255;
            const int min_g = 64;
            const int max_g = 255;
            const int min_b = 64;
            const int max_b = 255;

            color.red   = min_r + (max_r - min_r) * lit_factor;
            color.green = min_g + (max_g - min_g) * lit_factor;
            color.blue  = min_b + (max_b - min_b) * lit_factor;
            color.alpha = 255;
        }
    }

    // возможные частные случаи:
    // 1. две точки имеют равные ординаты, третья ниже них
    // 2. две точки имеют равные ординаты, третья выше них
    // 3. общий случай

    /// использовать алгоритм с упорядоченным списком ребер (вывести частный случай для трёх точек)
    {
        // сортировка точек. 1 - самая верхняя, 2 левее 3
        // параллельно сортируем вершины треугольника (для интерполяции нормали)
        if (1) {
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
        }

        // общий случай
        if (p1.y < p2.y && p1.y < p3.y)
        {
            int y = p1.y;
            double z = p1.z;

            double x_left = p1.x;
            double x_right = p1.x + 1;
            double dx1_2 = (p2.x - p1.x) / (p2.y - p1.y);
            double dx1_3 = (p3.x - p1.x) / (p3.y - p1.y);

            // часть отвечающая за интерполяцию нормалей
            Vec n_left = face.verts[0].normal;
            Vec n_right = face.verts[0].normal;
            Vec dn1_2 = (face.verts[1].normal - n_left) / (p2.y - p1.y);
            Vec dn1_3 = (face.verts[2].normal - n_right) / (p3.y - p1.y);

            if (dx1_2 < dx1_3)
            {
                if (p2.y == p3.y) // TODO: поменять местами if-else по частотам срабатывания
                {
                    while (y <= p2.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx1_2;
                        x_right += dx1_3;
                        n_left = n_left + dn1_2;
                        n_right = n_right + dn1_3;
                    }
                }
                else if (p2.y < p3.y)
                {
                    while (y <= p2.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx1_2;
                        x_right += dx1_3;
                        n_left = n_left + dn1_2;
                        n_right = n_right + dn1_3;
                    }

                    double dx2_3 = (p3.x - p2.x) / (p3.y - p2.y);
                    x_left = p2.x;
                    Vec dn2_3 = (face.verts[2].normal - face.verts[1].normal) / (p3.y - p2.y);
                    n_left = face.verts[1].normal;

                    while (y <= p3.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx2_3;
                        x_right += dx1_3;
                        n_left = n_left + dn2_3;
                        n_right = n_right + dn1_3;
                    }
                }
                else
                {
                    while (y <= p3.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx1_2;
                        x_right += dx1_3;
                        n_left = n_left + dn1_2;
                        n_right = n_right + dn1_3;
                    }

                    double dx3_2 = (p2.x - p3.x) / (p2.y - p3.y);
                    x_right = p3.x;
                    Vec dn3_2 = (face.verts[1].normal - face.verts[2].normal) / (p2.y - p3.y);
                    n_right = face.verts[2].normal;

                    while (y <= p2.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx1_2;
                        x_right += dx3_2;
                        n_left = n_left + dn1_2;
                        n_right = n_right + dn3_2;
                    }
                }
            }
            else
            {
                if (p2.y == p3.y) // TODO: поменять местами if-else по частотам срабатывания
                {
                    while (y <= p2.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx1_3;
                        x_right += dx1_2;
                        n_left = n_left + dn1_3;
                        n_right = n_right + dn1_2;
                    }
                }
                else if (p2.y < p3.y)
                {
                    while (y <= p2.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx1_3;
                        x_right += dx1_2;
                        n_left = n_left + dn1_3;
                        n_right = n_right + dn1_2;
                    }

                    double dx2_3 = (p3.x - p2.x) / (p3.y - p2.y);
                    x_right = p2.x;
                    Vec dn2_3 = (face.verts[2].normal - face.verts[1].normal) / (p3.y - p2.y);
                    n_right = face.verts[1].normal;

                    while (y <= p3.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx1_3;
                        x_right += dx2_3;
                        n_left = n_left + dn1_3;
                        n_right = n_right + dn2_3;
                    }
                }
                else
                {
                    while (y <= p3.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx1_3;
                        x_right += dx1_2;
                        n_left = n_left + dn1_3;
                        n_right = n_right + dn1_2;
                    }

                    double dx3_2 = (p2.x - p3.x) / (p2.y - p3.y);
                    x_left = p3.x;
                    Vec dn3_2 = (face.verts[1].normal - face.verts[2].normal) / (p2.y - p3.y);
                    n_left = face.verts[2].normal;

                    while (y <= p2.y)
                    {
                        Vec n = n_left;
                        Vec dn = (n_right - n_left) / (x_right - x_left);
                        for (int x = x_left; x < x_right; x++)
                        {
                            Pixel c = recomputeColor(n);
                            updatePixel(renderTarget, zbuffer, y, x, z, c);
                            n = n + dn;
                        }

                        y++;
                        x_left += dx3_2;
                        x_right += dx1_2;
                        n_left = n_left + dn3_2;
                        n_right = n_right + dn1_2;
                    }
                }
            }
        }
        else if (p1.y == p2.y) // случай p1.y == p2.y || p1.y == p3.y
        {
            if (p2.x < p1.x)
            {
                std::swap(p1, p2);
                std::swap(face.verts[0], face.verts[1]);
            }

            int y = p1.y;
            double z = p1.z;
            double x_left = p1.x;
            double x_right = p2.x + 1;

            double dx1_3 = (p3.x - p1.x) / (p3.y - p1.y);
            double dx2_3 = (p3.x - p2.x) / (p3.y - p1.y);

            Vec n_left = face.verts[0].normal;
            Vec n_right = face.verts[1].normal;
            Vec dn1_3 = (face.verts[2].normal - face.verts[0].normal) / (p3.y - p1.y);
            Vec dn2_3 = (face.verts[2].normal - face.verts[1].normal) / (p3.y - p1.y);

            while (y <= p3.y)
            {
                Vec n = n_left;
                Vec dn = (n_right - n_left) / (x_right - x_left);
                for (int x = x_left; x < x_right; x++)
                {
                    Pixel c = recomputeColor(n);
                    updatePixel(renderTarget, zbuffer, y, x, z, c);
                    n = n + dn;
                }

                y++;
                x_left += dx1_3;
                x_right += dx2_3;
                n_left = n_left + dn1_3;
                n_right = n_right + dn2_3;
            }
        }
        else
        {
            if (p3.x < p1.x)
            {
                std::swap(p1, p3);
                std::swap(face.verts[0], face.verts[2]);
            }

            int y = p1.y;
            double z = p1.z;
            double x_left = p1.x;
            double x_right = p3.x + 1;

            double dx1_2 = (p2.x - p1.x) / (p2.y - p1.y);
            double dx3_2 = (p2.x - p3.x) / (p2.y - p1.y);

            Vec n_left = face.verts[0].normal;
            Vec n_right = face.verts[2].normal;
            Vec dn1_2 = (face.verts[1].normal - face.verts[0].normal) / (p2.y - p1.y);
            Vec dn3_2 = (face.verts[1].normal - face.verts[2].normal) / (p2.y - p1.y);

            while (y <= p2.y)
            {
                Vec n = n_left;
                Vec dn = (n_right - n_left) / (x_right - x_left);
                for (int x = x_left; x < x_right; x++)
                {
                    Pixel c = recomputeColor(n);
                    updatePixel(renderTarget, zbuffer, y, x, z, c);
                    n = n + dn;
                }

                y++;
                x_left += dx1_2;
                x_right += dx3_2;
                n_left = n_left + dn1_2;
                n_right = n_right + dn3_2;
            }
        }
    }

    return StatusCode::Success;
}

static bool backFaceCooling(const Face& face, const Camera& camera)
{
    Vec p1 = projectToFrustrum(camera, face.verts[0].position);
    Vec p2 = projectToFrustrum(camera, face.verts[1].position);
    Vec p3 = projectToFrustrum(camera, face.verts[2].position);

    Vec norm = Core::cross(p2 - p1, p3 - p1);
    Vec dir = make_dir(0, 0, 1);

    double dot = Core::dot(dir, norm);
    return dot < 0.0;
}

static bool oculusCooling(const Face& face, const Camera& camera)
{
    Vec p1 = projectToFrustrum(camera, face.verts[0].position);
    Vec p2 = projectToFrustrum(camera, face.verts[1].position);
    Vec p3 = projectToFrustrum(camera, face.verts[2].position);

    unsigned int code1 = computeBitCode(p1);
    unsigned int code2 = computeBitCode(p2);
    unsigned int code3 = computeBitCode(p3);

    return code1 & code2 & code3;
}

static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2, Pixel color)
{
    return renderLine(renderTarget, p1.x, p1.y, p2.x, p2.y, color);
}

static bool same_projected(const Vec& v1, const Vec& v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

static Vec projectToFrustrum(const Camera& camera, const Vec& point)
{
    Vec res = camera.mvp * point;

    res.x /= res.z;
    res.y /= res.z;
    res.z = (res.z - camera.near) / (camera.far - camera.near) * 2 - 1;

    // TODO: вынести функции по работе с вьюпортом
#if USE_MIN_FIT
    if (camera.viewport.width > camera.viewport.height)
        res.x *= double(camera.viewport.height) / camera.viewport.width;
    else
        res.y *= double(camera.viewport.width) / camera.viewport.height;
#else
    if (camera.viewport.width > camera.viewport.height)
        res.y *= double(camera.viewport.height) / camera.viewport.width;
    else
        res.x *= double(camera.viewport.width) / camera.viewport.height;
#endif

    return res;
}

static unsigned int computeBitCode(const Vec& point)
{
    unsigned int code = 0x000000;

    const double side = 1.0;

    code |= (point.x < -side ? 1 : 0) << 0;
    code |= (point.x >  side ? 1 : 0) << 1;
    code |= (point.y < -side ? 1 : 0) << 2;
    code |= (point.y >  side ? 1 : 0) << 3;
    code |= (point.z < -side ? 1 : 0) << 4;
    code |= (point.z >  side ? 1 : 0) << 5;

    return code;
}

static Pixel recomputeColor(const Vec& normal)
{
    static Vec light = normalised(make_dir(-1, 2, 1));

    double lit_factor = dot(normalised(normal), light);
    if (lit_factor < 0) lit_factor = 0;

    Pixel color{};
    { // generate color from lit factor
        const int min_r = 32;
        const int max_r = 128;
        const int min_g = 64;
        const int max_g = 255;
        const int min_b = 48;
        const int max_b = 196;

        color.red   = min_r + (max_r - min_r) * lit_factor;
        color.green = min_g + (max_g - min_g) * lit_factor;
        color.blue  = min_b + (max_b - min_b) * lit_factor;
        color.alpha = 255;
    }

    return color;
}
