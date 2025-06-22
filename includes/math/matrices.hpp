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

    Matrix3x3 &operator*=(double scalar)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                (*this)(i, j) *= scalar;
        return *this;
    }
    Matrix3x3 &operator*=(const Matrix3x3 &other);
    Matrix3x3 &operator+=(const Matrix3x3 &other)
    {
        for (int i = 0; i < 9; i++)
            data[i] += other.data[i];
        return *this;
    }
    Matrix3x3 &operator-=(const Matrix3x3 &other)
    {
        for (int i = 0; i < 9; i++)
            data[i] -= other.data[i];
        return *this;
    }

    Quat4 ToQuaternion() const;

    Matrix3x3 Transpose() const
    {
        return Matrix3x3(
            data[0], data[3], data[6],
            data[1], data[4], data[7],
            data[2], data[5], data[8]);
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

inline Matrix3x3 operator*(Matrix3x3 l, const Matrix3x3 &r) { return l *= r; }
inline Matrix3x3 operator*(Matrix3x3 l, double scalar) { return l *= scalar; }
inline Vec3 operator*(const Vec3 &vec, const Matrix3x3 &matrix)
{
    return Vec3(
        matrix(0, 0) * vec.x + matrix(0, 1) * vec.y + matrix(0, 2) * vec.z,
        matrix(1, 0) * vec.x + matrix(1, 1) * vec.y + matrix(1, 2) * vec.z,
        matrix(2, 0) * vec.x + matrix(2, 1) * vec.y + matrix(2, 2) * vec.z);
}
inline Vec3 operator*(const Matrix3x3 &m, const Vec3 &vec) { return vec * m; }
inline Matrix3x3 operator+(Matrix3x3 l, const Matrix3x3 &r) { return l += r; }
inline Matrix3x3 operator-(Matrix3x3 l, const Matrix3x3 &r) { return l -= r; }

#endif