#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Core/math/Vec.hpp"
#include "Core/math/Mat.hpp"


namespace Core
{
    struct Transform
    {
        Vec position;
        Vec rotation;
        Vec scale;

        Mat matrix;
        bool dirty;
    };

    Transform make_transform();

    Transform inverse(const Transform& transform);

    void recalc_matrix(Transform& transform);

    void translate(Transform& transform, const Vec& offset);
    void rotate(Transform& transform, const Vec& angles);
    void scale(Transform& transform, const Vec& factor);

    Vec apply(const Transform& transform, const Vec& point);
}

#endif // TRANSFORM_HPP
