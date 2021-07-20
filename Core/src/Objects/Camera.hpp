#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vec.hpp"
#include "Mat.hpp"
#include "Rect.hpp"


namespace Core
{
    struct Camera
    {
        Rect viewport;
        Mat model_mat;
        Mat proj_mat;
        Mat mvp;
    };

    Camera make_camera(const Rect& viewport, double fov = 1.2217, double near = 0.1, double far = 1000.0);

    void recalc_mvp(Camera& camera);

    Vec project_point(const Camera& camera, const Vec& pos);
}

#endif // CMAERA_HPP
