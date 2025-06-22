#ifndef MATRICES_HPP
#define MATRICES_HPP

#include "vectors.hpp"
#include "quaternions.hpp"

struct Matrix3x3
{
    double data[9];

    Matrix3x3()
    {
        data[0] = 0.0;
        data[1] = 0.0;
        data[2] = 0.0;
        data[3] = 0.0;
        data[4] = 0.0;
        data[5] = 0.0;
        data[6] = 0.0;
        data[7] = 0.0;
        data[8] = 0.0;
    };

    Matrix3x3(double d0, double d1, double d2,
              double d3, double d4, double d5,
              double d6, double d7, double d8)
    {
        data[0] = d0;
        data[1] = d1;
        data[2] = d2;
        data[3] = d3;
        data[4] = d4;
        data[5] = d5;
        data[6] = d6;
        data[7] = d7;
        data[8] = d8;
    }
    double &operator()(int row, int col)
    {
        return data[row * 3 + col];
    }
    const double &operator()(int row, int col) const
    {
        return data[row * 3 + col];
    }
    Matrix3x3 operator*(const Matrix3x3 &other) const
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
        return result;
    }
    Vec3 operator*(const Vec3 &vec) const
    {
        return Vec3(
            data[0] * vec.x + data[1] * vec.y + data[2] * vec.z,
            data[3] * vec.x + data[4] * vec.y + data[5] * vec.z,
            data[6] * vec.x + data[7] * vec.y + data[8] * vec.z);
    }

    Quat4 ToQuaternion() const
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
    Matrix3x3 Transpose() const {
        return Matrix3x3(
            data[0], data[3], data[6],
            data[1], data[4], data[7],
            data[2], data[5], data[8]
        );
    }

    static Matrix3x3 Identity()
    {
        Matrix3x3 identity;
        identity(0, 0) = 1.0;
        identity(1, 1) = 1.0;
        identity(2, 2) = 1.0;
        return identity;
    }
};

#endif