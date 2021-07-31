#ifndef MATERIALIMP_HPP
#define MATERIALIMP_HPP

#include "Core/Objects/Material.hpp"


namespace Core
{
    template<size_t lightCount>
    Color compute_color(const Material& material, const arr_t<Vec, lightCount>& lights, const Vec& view, const Vec& normal)
    {
        const double ambient = 0.1;

        Color color = ambient * material.ambientColor;

        for (size_t i = 0; i < lightCount; i++)
        {
            Vec light;
            if (get(lights, i, light))
            {
                Vec Rm = 2 * dot(-light, normal) * normal + light;

                double Lm_N = std::max(0.0, dot(-light, normal));
                double Rm_V = std::max(0.0, dot(Rm, -view));
                Rm_V = std::pow(Rm_V, material.specularHighlight);

                color += material.diffuseColor * Lm_N + material.specularColor * Rm_V;
            }
        }

        return color;
    }
}

#endif // MATERIALIMP_HPP
