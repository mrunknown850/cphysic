#ifndef QUATERNIONS_HPP
#define QUATERNIONS_HPP

#include "vectors.hpp"

struct Quat4
{
    double w, x, y, z;

    Quat4() : w(1), x(0), y(0), z(0) {}
    Quat4(double _w, Vec3 axis) : w(_w)
    {
        Vec4 temp = Vec4(_w, axis.x, axis.y, axis.z);
        if (temp.IsZero())
            temp.w = 1;
        else
            temp.Normalize();
        w = temp.w;
        x = temp.x;
        y = temp.y;
        z = temp.z;
    }
    Quat4(double _w, double _x, double _y, double _z)
    {
        Vec4 temp = Vec4(_w, _x, _y, _z);
        if (temp.IsZero())
            temp.w = 1;
        else
            temp.Normalize();
        w = temp.w;
        x = temp.x;
        y = temp.y;
        z = temp.z;
    }

    Quat4 &Normalize()
    {
        Vec4 temp = Vec4(w, x, y, z).Normalize();
        w = temp.w;
        x = temp.x;
        y = temp.y;
        z = temp.z;
        return *this;
    }
    Quat4 operator-() const { return Quat4(w, -x, -y, -z); }
    Quat4 &operator+=(const Quat4 &other)
    {
        w += other.w;
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Quat4 &operator*=(const Quat4 &other)
    {
        double w1 = w, x1 = x, y1 = y, z1 = z;
        double w2 = other.w, x2 = other.x, y2 = other.y, z2 = other.z;
        w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
        x = w1 * x2 + w2 * x1 + y1 * z2 - z1 * y2;
        y = w1 * y2 + w2 * y1 + z1 * x2 - x1 * z2;
        z = w1 * z2 + w2 * z1 + x1 * y2 - y1 * x2;
        return *this;
    }
};

inline Quat4 operator+(Quat4 l, const Quat4 &r) { return l += r; }
inline Quat4 operator*(Quat4 l, const Quat4 &r) { return l *= r; }
inline Vec3 operator*(const Vec3 &l, const Quat4 &Q)
{
    Quat4 P = Quat4(0, l);
    Quat4 R = Q * P * -Q;
    return Vec3(R.x, R.y, R.z);
}

#endif