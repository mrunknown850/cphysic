#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <cmath>
#include "config.hpp"

// Vectors
struct Vec3
{
    double x, y, z;

    constexpr Vec3() : x(0), y(0), z(0) {}
    constexpr Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    // Direct return
    constexpr Vec3 operator-() const { return Vec3(-x, -y, -z); }
    Vec3 &operator+=(const Vec3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vec3 &operator-=(const Vec3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vec3 &operator*=(const double scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    Vec3 &operator/=(const double scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    constexpr double Dot(const Vec3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }
    constexpr double LengthSquared() const
    {
        return this->Dot(*this);
    }
    constexpr Vec3 &Normalize()
    {
        if (this->IsZero())
        {
            return *this;
        }
        double length = sqrt(this->LengthSquared());
        x /= length;
        y /= length;
        z /= length;
        return *this;
    }
    bool IsZero() const
    {
        if (!(-EPSILON <= x && x <= EPSILON))
            return false;
        if (!(-EPSILON <= y && y <= EPSILON))
            return false;
        if (!(-EPSILON <= z && z <= EPSILON))
            return false;
        return true;
    }
};

// Vector Product
inline double Dot(const Vec3 &l, const Vec3 &r)
{
    return l.Dot(r);
}
inline Vec3 Cross(const Vec3 &l, const Vec3 &r)
{
    return Vec3(
        l.y * r.z - l.z * r.y,
        l.z * r.x - l.x * r.z,
        l.x * r.y - l.y * r.x);
}

// New object return
inline Vec3 operator+(Vec3 l, const Vec3 &r) { return l += r; }
inline Vec3 operator-(Vec3 l, const Vec3 &r) { return l -= r; }
inline Vec3 operator*(Vec3 l, const double scalar) { return l *= scalar; }
inline Vec3 operator*(double scalar, Vec3 r) { return r *= scalar; }
inline double operator*(const Vec3 &l, const Vec3 &r) { return l.Dot(r); }
inline Vec3 operator/(Vec3 l, double scalar) { return l /= scalar; }
inline Vec3 operator^(const Vec3 &l, const Vec3 &r) { return Cross(l, r); }

// Comparison
inline bool operator==(const Vec3 &l, const Vec3 &r)
{
    return l.x == r.x && l.y == r.y && l.z == r.z;
}

struct Vec4
{
    double w, x, y, z;

    constexpr Vec4() : w(0), x(0), y(0), z(0) {}
    constexpr Vec4(double _w, double _x, double _y, double _z) : w(_w), x(_x), y(_y), z(_z) {}

    constexpr Vec4 operator-() const { return Vec4(-w, -x, -y, -z); }
    Vec4 &operator+=(const Vec4 &other)
    {
        w += other.w;
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vec4 &operator-=(const Vec4 &other)
    {
        w += other.w;
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vec4 &operator*=(const double scalar)
    {
        w *= scalar;
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    Vec4 &operator/=(const double scalar)
    {
        w /= scalar;
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    constexpr double Dot(const Vec4 &other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    constexpr double LengthSquared() const
    {
        return this->Dot(*this);
    }
    constexpr Vec4 &Normalize()
    {
        if (this->IsZero())
            return *this;
        double length = sqrt(this->LengthSquared());
        x /= length;
        y /= length;
        z /= length;
        w /= length;
        return *this;
    }
    bool IsZero() const
    {
        if (!(-EPSILON <= w && w <= EPSILON))
            return false;
        if (!(-EPSILON <= x && x <= EPSILON))
            return false;
        if (!(-EPSILON <= y && y <= EPSILON))
            return false;
        if (!(-EPSILON <= z && z <= EPSILON))
            return false;
        return true;
    }
};

// Vector Product
inline double Dot(const Vec4 &l, const Vec4 &r)
{
    return l.Dot(r);
}

// New object return
inline Vec4 operator+(Vec4 l, const Vec4 &r) { return l += r; }
inline Vec4 operator-(Vec4 l, const Vec4 &r) { return l -= r; }
inline Vec4 operator*(Vec4 l, const double scalar) { return l *= scalar; }
inline Vec4 operator*(double scalar, Vec4 r) { return r *= scalar; }
inline double operator*(const Vec4 &l, const Vec4 &r) { return l.Dot(r); }
inline Vec4 operator/(Vec4 l, double scalar) { return l /= scalar; }

// Comparison
inline bool operator==(const Vec4 &l, const Vec4 &r)
{
    return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
}

#endif