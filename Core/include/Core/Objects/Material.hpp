#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Core/containers/arr_t.hpp"
#include "Core/containers/vect_t.hpp"
#include "Core/common/Color.hpp"
#include "Core/Objects/Light.hpp"


namespace Core
{
    struct Mat;
    struct Scene;

    struct Material
    {
        Color ambientColor;
        Color diffuseColor;
        Color specularColor;
        double specularHighlight;
        double opacity;
    };

    Material make_material();

    template<size_t lightCount>
    Color compute_color(const Material& material, const arr_t<Light, lightCount>& lights, const Vec& view, const Vec& normal);

    Color compute_color(const Material& material, const vect_t<Light>& lights, const Vec& view, const Vec& normal);
    Color compute_color(const Material& material, const vect_t<Light>& lights, const Vec& pos, const Vec& view, const Vec& normal);
    Color compute_color(const Material& material, const vect_t<Light>& lights, const Mat& view_mat, const Vec& view, const Vec& normal);
    Color compute_color(const Material& material, const Scene& scene, const vect_t<Light>& lights, const Vec& pos, const Vec& view, const Vec& normal);
}

#include "Core/Objects/MaterialImp.hpp"

#endif // MATERIAL_HPP
