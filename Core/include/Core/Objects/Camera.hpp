#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Core/common/math/Vec.hpp"
#include "Core/common/math/Mat.hpp"
#include "Core/common/math/Rect.hpp"

// флаг для компановки рабочего окна в доступную область.
// если 1 - рабочее окно будет расширено до пределов доступной области (не рекомендуется),
// если 0 - рабочее окно будет обрезано по доступной области (менее багуемо).
#define USE_MIN_FIT 0

namespace Core
{
    struct Camera
    {
        Rect viewport;
        double fov;
        double near;
        double far;
        Vec eye;
        double pitch;
        double yaw;
        Mat model_mat;
        Mat proj_mat;
        Mat mvp;
    };

    Camera make_camera(double fov = 1.2217, double near = 80.0, double far = 1000.0);

    void update_viewport(Camera& camera, const Rect& viewport);
    void recalc_mvp(Camera& camera, const Mat& model_mat);
    void update_transformation(Camera& camera);

    Vec view_dir(const Camera& camera);
    Vec view_pos(const Camera& camera);

    Vec project_frustrum(const Camera& camera, const Vec& pos);
    Vec viewport_adjust(const Camera& camera, const Vec& pos);
    Vec project_point(const Camera& camera, const Vec& pos);
}

#endif // CMAERA_HPP
