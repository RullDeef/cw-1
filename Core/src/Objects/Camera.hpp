#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ext_math.hpp"


namespace Core
{
    struct Camera
    {
        mat model_mat;
        double fov;
        double near;
        double far;
    };

    Camera make_camera(double fov = 1.2217, double near = 0.1, double far = 1000.0);

    mat get_camera_mat(const Camera& camera, int vwidth, int vheight);
}

#endif // CMAERA_HPP
