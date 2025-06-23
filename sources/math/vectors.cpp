#include "vectors.hpp"
#include "matrices.hpp"

Matrix3x3 Vec3::SelfInverseOuter() const
{
    return Matrix3x3(
        x * x, x * y, x * z,
        y * x, y * y, y * z,
        z * x, z * y, z * z);
}