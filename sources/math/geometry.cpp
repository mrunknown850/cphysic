#include <cmath>
#include "geometry.hpp"
#include "object.hpp"
#include "config.hpp"

void ProjectBox(const Vec3 &center, const std::vector<Vec3> &axis,
                const Vec3 &halfExtends, const Vec3 &axisProj, double &minProj, double &maxProj)
{
    double r = halfExtends.x * std::abs(axis[0] * axisProj) +
               halfExtends.y * std::abs(axis[1] * axisProj) +
               halfExtends.z * std::abs(axis[2] * axisProj);
    double s = center * axisProj;
    minProj = s - r;
    maxProj = s + r;
}

bool Overlap(double min1, double max1, double min2, double max2)
{
    return (max1 >= min2 - EPSILON && max2 >= min1 - EPSILON);
}

bool BoxBoxCollision(const Box &b1, const Box &b2)
{
    double min1, min2, max1, max2;
    Vec3 axis;

    Vec3 b1_center = b1.GetWorldCenter();
    std::vector<Vec3> b1_axis = b1.GetNormalAxis();
    Vec3 b1_extends = b1.GetHalfExtends();

    Vec3 b2_center = b2.GetWorldCenter();
    std::vector<Vec3> b2_axis = b2.GetNormalAxis();
    Vec3 b2_extends = b2.GetHalfExtends();

    for (const Vec3 &axis : b1_axis)
    {
        ProjectBox(b1_center, b1_axis, b1_extends, axis, min1, max1);
        ProjectBox(b2_center, b2_axis, b2_extends, axis, min2, max2);
        if (!Overlap(min1, max1, min2, max2))
            return false;
    }

    for (const Vec3 &axis : b2_axis)
    {
        ProjectBox(b1_center, b1_axis, b1_extends, axis, min1, max1);
        ProjectBox(b2_center, b2_axis, b2_extends, axis, min2, max2);
        if (!Overlap(min1, max1, min2, max2))
            return false;
    }

    for (const Vec3 &a : b1_axis)
    {
        for (const Vec3 &b : b2_axis)
        {
            axis = a ^ b;
            if (axis.IsZero())
                continue;

            ProjectBox(b1_center, b1_axis, b1_extends, axis, min1, max1);
            ProjectBox(b2_center, b2_axis, b2_extends, axis, min2, max2);
            if (!Overlap(min1, max1, min2, max2))
                return false;
        }
    }
    return true;
}

bool Box::CollidesWith(const Geometry &other) const
{
    if (other.GetType() == GeometryType::BOX)
    {
        const Box *otherBox = dynamic_cast<const Box *>(&other);
        if (otherBox)
            return BoxBoxCollision(*this, *otherBox);
        return false;
    }
    return false;
}

std::vector<Vec3> Box::GetNormalAxis() const
{
    std::vector<Vec3> a;
    a.reserve(3);

    a.emplace_back(Vec3(1, 0, 0) * this->GetWorldRotation());
    a.emplace_back(Vec3(0, 1, 0) * this->GetWorldRotation());
    a.emplace_back(Vec3(0, 0, 1) * this->GetWorldRotation());
    return a;
}

Vec3 Geometry::GetWorldCenter() const { return offset + object->GetPosition(); }
Quat4 Geometry::GetWorldRotation() const {
    Quat4 result = rotation * object->GetRotation();
    result.Normalize();
    return result;
}