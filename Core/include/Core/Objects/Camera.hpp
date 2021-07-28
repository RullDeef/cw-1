#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Core/common/math/Vec.hpp"
#include "Core/common/math/Mat.hpp"
#include "Core/common/math/Rect.hpp"


namespace Core
{
    struct Camera
    {
        Rect viewport;
        double fov;
        double near;
        double far;
        Mat model_mat;
        Mat proj_mat;
        Mat mvp;
    };

    Camera make_camera(double fov = 1.2217, double near = 0.1, double far = 1000.0);

    void update_viewport(Camera& camera, const Rect& viewport);
    void recalc_mvp(Camera& camera);

    Vec view_dir(const Camera& camera);
    Vec view_pos(const Camera& camera);

    Vec project_point(const Camera& camera, const Vec& pos);
}

#endif // CMAERA_HPP
