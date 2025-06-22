#include "matrices.hpp"

Matrix3x3 &Matrix3x3::operator*=(const Matrix3x3 &other)
{
    Matrix3x3 result;
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            result(row, col) = 0.0;
            for (int k = 0; k < 3; ++k)
            {
                result(row, col) += (*this)(row, k) * other(k, col);
            }
        }
    }
    *this = result;
    return *this;
}
Quat4 Matrix3x3::ToQuaternion() const
{
    // Convert the 3x3 matrix to a quaternion
    double trace = data[0] + data[4] + data[8];
    double w, x, y, z;
    if (trace > 0)
    {
        double s = sqrt(trace + 1.0) * 2; // S= 4 * w
        w = 0.25 * s;
        x = (data[7] - data[5]) / s;
        y = (data[2] - data[6]) / s;
        z = (data[3] - data[1]) / s;
    }
    else if ((data[0] > data[4]) && (data[0] > data[8]))
    {
        double s = sqrt(1.0 + data[0] - data[4] - data[8]) * 2; // S= 4 * x
        w = (data[7] - data[5]) / s;
        x = 0.25 * s;
        y = (data[1] + data[3]) / s;
        z = (data[2] + data[6]) / s;
    }
    else if (data[4] > data[8])
    {
        double s = sqrt(1.0 + data[4] - data[0] - data[8]) * 2; // S= 4 * y
        w = (data[2] - data[6]) / s;
        x = (data[1] + data[3]) / s;
        y = 0.25 * s;
        z = (data[5] + data[7]) / s;
    }
    else
    {
        double s = sqrt(1.0 + data[8] - data[0] - data[4]) * 2; // S= 4 * z
        w = (data[3] - data[1]) / s;
        x = (data[2] + data[6]) / s;
        y = (data[5] + data[7]) / s;
        z = 0.25 * s;
    }
    return Quat4(w, x, y, z);
}
