#include "quaternions.hpp"
#include "matrices.hpp"

Matrix3x3 Quat4::ToMatrix() const
{
    {
        Matrix3x3 M;
        M(0, 0) = 1 - 2 * (y * y + z * z);
        M(0, 1) = 2 * (x * y - w * z);
        M(0, 2) = 2 * (x * z + w * y);
        M(1, 0) = 2 * (x * y + w * z);
        M(1, 1) = 1 - 2 * (x * x + z * z);
        M(1, 2) = 2 * (y * z - w * x);
        M(2, 0) = 2 * (x * z - w * y);
        M(2, 1) = 2 * (y * z + w * x);
        M(2, 2) = 1 - 2 * (x * x + y * y);
        return M;
    }
}