#include <gtest/gtest.h>
#include "math/matrices.hpp"
#include "math/quaternions.hpp"

TEST(QuaternionMatrixTest, QuaternionToMatrixAndBackIdentity)
{
    Quat4 q; // Identity quaternion
    Matrix3x3 m = q.ToMatrix();
    Quat4 q2 = m.ToQuaternion();
    EXPECT_NEAR(q2.w, 1.0, 1e-12);
    EXPECT_NEAR(q2.x, 0.0, 1e-12);
    EXPECT_NEAR(q2.y, 0.0, 1e-12);
    EXPECT_NEAR(q2.z, 0.0, 1e-12);
}

TEST(QuaternionMatrixTest, QuaternionToMatrixAndBack90degX)
{
    double angle = M_PI / 2;
    double s = sin(angle / 2);
    double c = cos(angle / 2);
    Quat4 q(c, s, 0, 0); // 90 deg around X
    Matrix3x3 m = q.ToMatrix();
    Quat4 q2 = m.ToQuaternion();
    // q and q2 may differ in sign, so compare absolute values
    EXPECT_NEAR(fabs(q2.w), fabs(q.w), 1e-12);
    EXPECT_NEAR(fabs(q2.x), fabs(q.x), 1e-12);
    EXPECT_NEAR(fabs(q2.y), fabs(q.y), 1e-12);
    EXPECT_NEAR(fabs(q2.z), fabs(q.z), 1e-12);
}

TEST(QuaternionMatrixTest, QuaternionToMatrixAndBack90degY)
{
    double angle = M_PI / 2;
    double s = sin(angle / 2);
    double c = cos(angle / 2);
    Quat4 q(c, 0, s, 0); // 90 deg around Y
    Matrix3x3 m = q.ToMatrix();
    Quat4 q2 = m.ToQuaternion();
    EXPECT_NEAR(fabs(q2.w), fabs(q.w), 1e-12);
    EXPECT_NEAR(fabs(q2.x), fabs(q.x), 1e-12);
    EXPECT_NEAR(fabs(q2.y), fabs(q.y), 1e-12);
    EXPECT_NEAR(fabs(q2.z), fabs(q.z), 1e-12);
}

TEST(QuaternionMatrixTest, QuaternionToMatrixAndBack90degZ)
{
    double angle = M_PI / 2;
    double s = sin(angle / 2);
    double c = cos(angle / 2);
    Quat4 q(c, 0, 0, s); // 90 deg around Z
    Matrix3x3 m = q.ToMatrix();
    Quat4 q2 = m.ToQuaternion();
    EXPECT_NEAR(fabs(q2.w), fabs(q.w), 1e-12);
    EXPECT_NEAR(fabs(q2.x), fabs(q.x), 1e-12);
    EXPECT_NEAR(fabs(q2.y), fabs(q.y), 1e-12);
    EXPECT_NEAR(fabs(q2.z), fabs(q.z), 1e-12);
}

TEST(QuaternionMatrixTest, MatrixRotatesVector)
{
    // 90 deg rotation around Z axis
    double angle = M_PI / 2;
    double s = sin(angle / 2);
    double c = cos(angle / 2);
    Quat4 q(c, 0, 0, s);
    Matrix3x3 m = q.ToMatrix();
    Vec3 v(1, 0, 0);
    Vec3 r = m * v;
    EXPECT_NEAR(r.x, 0.0, 1e-12);
    EXPECT_NEAR(r.y, 1.0, 1e-12);
    EXPECT_NEAR(r.z, 0.0, 1e-12);
}
