#include "Math/Matrix.hpp"


Matrix::Matrix()
{
    for (double& elem : data)
        elem = 0.0;
}

Matrix::Matrix(const double *mat)
{
    for (int i = 0; i < 16; i++)
        data[i] = mat[i];
}

Matrix Matrix::make_mat_id()
{
    Matrix res = Matrix();

    for (int i = 0; i < 16; i += 5)
        res.data[i] = 1;

    return res;
}

Matrix Matrix::make_mat_translation(double dx, double dy, double dz)
{
    return Matrix();
}

