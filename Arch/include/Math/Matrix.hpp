#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Math/Vector.hpp"

class Matrix
{
public:
    Matrix();

    static Matrix make_mat_id();
    static Matrix make_mat_translation(double dx, double dy, double dz);

protected:
    explicit Matrix(const double mat[16]);

private:
    double data[16];
};

#endif //MATRIX_HPP
