#include <cmath>
#include <algorithm>
#include "geometry.hpp"
#include "object.hpp"
#include "config.hpp"

#pragma region Box-Box Collision Helper Functions
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
std::vector<Vec3> Box::GetNormalAxis() const
{
    std::vector<Vec3> a;
    a.reserve(3);

    a.emplace_back(Vec3(1, 0, 0) * this->GetWorldRotation());
    a.emplace_back(Vec3(0, 1, 0) * this->GetWorldRotation());
    a.emplace_back(Vec3(0, 0, 1) * this->GetWorldRotation());
    return a;
}
#pragma endregion
#pragma region Sphere-Sphere Collision Helper Functions
bool SphereSphereCollision(const Sphere &s1, const Sphere &s2)
{
    double sr = s1.GetRadius() + s2.GetRadius();
    double distSquared = (s1.GetWorldCenter() - s2.GetWorldCenter()).LengthSquared();
    return (distSquared <= sr * sr);
}
#pragma endregion
#pragma region Sphere-Box Collision Helper Functions
bool BoxSphereCollision(const Box &box, const Sphere &sphere)
{
    const Vec3 obbCenter = box.GetWorldCenter();
    const Vec3 obbHalfExtends = box.GetHalfExtends();
    const std::vector<Vec3> obbAxis = box.GetNormalAxis();

    Vec3 V = sphere.GetWorldCenter() - obbCenter;

    double localX = V.Dot(obbAxis[0]);
    double localY = V.Dot(obbAxis[1]);
    double localZ = V.Dot(obbAxis[2]);

    double closestX = std::clamp(localX, -obbHalfExtends.x, obbHalfExtends.x);
    double closestY = std::clamp(localY, -obbHalfExtends.y, obbHalfExtends.y);
    double closestZ = std::clamp(localZ, -obbHalfExtends.z, obbHalfExtends.z);

    double distX = localX - closestX;
    double distY = localY - closestY;
    double distZ = localZ - closestZ;

    double distSqr = distX * distX + distY * distY + distZ * distZ;
    double sphereRadiusSq = sphere.GetRadius() * sphere.GetRadius();

    return distSqr <= sphereRadiusSq;
}
#pragma endregion

bool Box::CollidesWith(const Geometry &other) const
{
    if (other.GetType() == GeometryType::BOX)
    {
        const Box *otherBox = dynamic_cast<const Box *>(&other);
        if (otherBox)
            return BoxBoxCollision(*this, *otherBox);
        return false;
    }
    else if (other.GetType() == GeometryType::SPHERE)
    {
        const Sphere *otherSphere = dynamic_cast<const Sphere *>(&other);
        if (otherSphere)
            return BoxSphereCollision(*this, *otherSphere);
        return false;
    }
    return false;
}
bool Sphere::CollidesWith(const Geometry &other) const
{
    if (other.GetType() == GeometryType::SPHERE)
    {
        const Sphere *otherSphere = dynamic_cast<const Sphere *>(&other);
        if (otherSphere)
            return SphereSphereCollision(*this, *otherSphere);
        return false;
    }
    else if (other.GetType() == GeometryType::BOX)
    {
        const Box *otherBox = dynamic_cast<const Box *>(&other);
        if (otherBox)
            return BoxSphereCollision(*otherBox, *this);
        return false;
    }
    return false;
}

// Box specifics
Matrix3x3 Box::GetLocalInertiaMatrix() const
{
    double mass = this->object->GetMass();
    Matrix3x3 inertiaMatrix;
    const Vec3 fullExtends = this->GetHalfExtends() * 2.0;
    const Vec3 offset = this->GetLocalOffset();

    inertiaMatrix(0, 0) = 1.0 / 12.0 * mass * (fullExtends.y * fullExtends.y + fullExtends.z * fullExtends.z);
    inertiaMatrix(1, 1) = 1.0 / 12.0 * mass * (fullExtends.x * fullExtends.x + fullExtends.z * fullExtends.z);
    inertiaMatrix(2, 2) = 1.0 / 12.0 * mass * (fullExtends.y * fullExtends.y + fullExtends.x * fullExtends.x);

    Matrix3x3 rotationMatrix = this->GetWorldRotation().ToMatrix();
    Matrix3x3 rotatedMatrix = (rotationMatrix * inertiaMatrix) * rotationMatrix.Transpose();
    Matrix3x3 res = rotatedMatrix + (Matrix3x3::Identity() * offset.LengthSquared() - offset.SelfInverseOuter()) * mass;

    return res;
}

Matrix3x3 Sphere::GetLocalInertiaMatrix() const
{
    double mass = this->object->GetMass();
    double radius = this->GetRadius();
    const Vec3 offset = this->GetLocalOffset();

    double sphere_angular_inertia = 2.0 / 5.0 * mass * radius * radius;
    Matrix3x3 inertiaLocal = Matrix3x3::Identity() * sphere_angular_inertia;
    Matrix3x3 offsetOuter = offset.SelfInverseOuter();
    Matrix3x3 paralelAxis = (Matrix3x3::Identity() * offset.LengthSquared() - offsetOuter) * mass;
    Matrix3x3 res = inertiaLocal + paralelAxis;
    return res;
}

// General functions
Vec3 Geometry::GetWorldCenter() const { return offset + object->GetPosition(); }
Quat4 Geometry::GetWorldRotation() const
{
    Quat4 result = rotation * object->GetRotation();
    result.Normalize();
    return result;
}