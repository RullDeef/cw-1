#include "Core/math/Ray.hpp"
#include "Core/math/Mat.hpp"
#include "Core/Objects/Material.hpp"
#include "Core/Scene/Scene.hpp"

using namespace Core;


Material Core::make_material()
{
    Material mat{};

    mat.ambientColor = Colors::white;
    mat.diffuseColor = Colors::white;
    mat.specularColor = Colors::white;

    mat.opacity = 1.0;
    mat.specularHighlight = 1.0;

    return mat;
}

Color Core::compute_color(const Material& material, const vect_t<Light>& lights, const Vec& view, const Vec& normal)
{
    // const double ambient = 0.1;
    Color color = Colors::black; // ambient * material.ambientColor;

    for (size_t i = 0; i < lights.size; i++)
    {
        Light light{};
        if (get(lights, i, light))
        {
            if (light.type == LightType::Ambient)
            {
                color += light.intensity * light.color * material.ambientColor;
            }
            else if (light.type == LightType::Directional)
            {
                Vec dir = light.direction;
                Vec Rm = 2 * dot(-dir, normal) * normal + dir;

                double Lm_N = std::max(0.0, dot(-dir, normal));
                double Rm_V = std::max(0.0, dot(Rm, -view));
                Rm_V = std::pow(Rm_V, material.specularHighlight);

                color += light.intensity * material.diffuseColor * light.color * (Lm_N + Rm_V);
            }
        }
    }

    return color;
}

// handles point lights as well
Color Core::compute_color(const Material& material, const vect_t<Light>& lights, const Vec& pos, const Vec& view, const Vec& normal)
{
    Color color = Colors::black;

    for (size_t i = 0; i < lights.size; i++)
    {
        Light light{};
        if (get(lights, i, light))
        {
            if (light.type == LightType::Ambient)
            {
                color += light.intensity * light.color * material.ambientColor;
            }
            else if (light.type == LightType::Directional)
            {
                Vec dir = light.direction;
                Vec Rm = 2 * dot(-dir, normal) * normal + dir;

                double Lm_N = std::max(0.0, dot(-dir, normal));
                double Rm_V = std::max(0.0, dot(Rm, -view));
                Rm_V = std::pow(Rm_V, material.specularHighlight);

                color += light.intensity * material.diffuseColor * light.color * (Lm_N + Rm_V);
            }
            else // type == LightType::Point
            {
                double dis = length(light.position - pos) / light.radius;
                double attenuation = light.attenuation.x + light.attenuation.y * dis + light.attenuation.z * dis * dis;

                color += light.intensity / attenuation * light.color * material.ambientColor;
            }
        }
    }

    return color;
}

Color Core::compute_color(const Material& material, const vect_t<Light>& lights, const Mat& view_mat, const Vec& view, const Vec& normal)
{
    Color color = Colors::black;

    for (size_t i = 0; i < lights.size; i++)
    {
        Light light{};
        if (get(lights, i, light))
        {
            if (light.type == LightType::Ambient)
            {
                color += light.intensity * light.color * material.ambientColor;
            }
            else if (light.type == LightType::Directional)
            {
                Vec dir = normalized(view_mat * light.direction);
                Vec Rm = 2 * dot(-dir, normal) * normal + dir;

                double Lm_N = std::max(0.0, dot(-dir, normal));
                double Rm_V = std::max(0.0, dot(Rm, -view));
                Rm_V = std::pow(Rm_V, material.specularHighlight);

                color += light.intensity * material.diffuseColor * light.color * (Lm_N + Rm_V);
            }
        }
    }

    return color;
}

Color Core::compute_color(const Material& material, const Scene& scene, const vect_t<Light>& lights, const Vec& pos, const Vec& view, const Vec& normal)
{
    Color color = Colors::black;

    for (size_t i = 0; i < lights.size; i++)
    {
        Light light{};
        if (get(lights, i, light))
        {
            if (light.type == LightType::Ambient)
            {
                color += light.intensity * light.color * material.ambientColor;
            }
            else if (light.type == LightType::Directional)
            {
                double t;
                Mesh mesh{};
                Ray ray = make_ray(pos - 0.01 * light.direction, -light.direction);
                if (ray_intersects(t, ray, mesh, scene))
                {
                    color = Colors::green; /// TODO: fix bug. Ray does not collide with meshes
                    break;
                }
                else
                {
                    Vec dir = normalized(light.direction);
                    Vec Rm = 2 * dot(-dir, normal) * normal + dir;

                    double Lm_N = std::max(0.0, dot(-dir, normal));
                    double Rm_V = std::max(0.0, dot(Rm, -view));
                    Rm_V = std::pow(Rm_V, material.specularHighlight);

                    color += light.intensity * material.diffuseColor * light.color * (Lm_N + Rm_V);
                }
            }
        }
    }

    return color;
}
