// filepath: /home/MrUnknown850/Documents/cphysic/tests/test_geometry_inertia.cpp
#include <gtest/gtest.h>
#include "math/geometry.hpp"
#include "physic/object.hpp"
#include <memory>
#include <cmath>

TEST(BoxInertiaMatrixTest, AxisAlignedBoxAtOrigin)
{
    // Box of size 2x4x6 (halfExtends = 1,2,3), mass = 12, at origin, no rotation, no offset
    auto box = std::make_unique<Box>(Vec3{1, 2, 3}, nullptr);
    Object obj(12.0, std::move(box));
    const Matrix3x3& inertia = obj.GetInertiaMatrix();

    // Analytical inertia for box at origin, axis-aligned:
    // Ixx = 1/12 * m * (h^2 + d^2)
    // Iyy = 1/12 * m * (w^2 + d^2)
    // Izz = 1/12 * m * (w^2 + h^2)
    double w = 2.0, h = 4.0, d = 6.0, m = 12.0;
    double Ixx = 1.0/12.0 * m * (h*h + d*d);
    double Iyy = 1.0/12.0 * m * (w*w + d*d);
    double Izz = 1.0/12.0 * m * (w*w + h*h);

    EXPECT_NEAR(inertia(0,0), Ixx, 1e-10);
    EXPECT_NEAR(inertia(1,1), Iyy, 1e-10);
    EXPECT_NEAR(inertia(2,2), Izz, 1e-10);
}

TEST(BoxInertiaMatrixTest, OffsetBox)
{
    // Box of size 2x2x2 (halfExtends = 1,1,1), mass = 3, offset from parent at (5,0,0)
    auto box = std::make_unique<Box>(Vec3{1, 1, 1}, nullptr);
    box->SetLocalOffset(5, 0, 0);
    Object obj(3.0, std::move(box));
    const Matrix3x3& inertia = obj.GetInertiaMatrix();

    // Parallel axis theorem: I_new = I_cm + m*d^2 (for each axis)
    double m = 3.0, a = 2.0;
    double I_cm = 1.0/6.0 * m * a * a; // cube, axis-aligned
    double d2 = 25.0; // offset^2
    double I_expected_xx = I_cm;           // No offset contribution
    double I_expected_yy = I_cm + m * 25;  // Offset in y
    double I_expected_zz = I_cm + m * 25;  // Offset in z

    EXPECT_NEAR(inertia(0,0), I_expected_xx, 1e-10);
    EXPECT_NEAR(inertia(1,1), I_expected_yy, 1e-10);
    EXPECT_NEAR(inertia(2,2), I_expected_zz, 1e-10);
}

TEST(BoxInertiaMatrixTest, RotatedBox)
{
    // Box of size 2x2x2 (halfExtends = 1,1,1), mass = 2, rotated 90 deg around Z
    auto box = std::make_unique<Box>(Vec3{1, 1, 1}, nullptr);
    Quat4 rotZ90(std::cos(M_PI/4), 0, 0, std::sin(M_PI/4)); // 90 deg about Z
    box->SetLocalRotation(rotZ90);
    Object obj(2.0, std::move(box));
    const Matrix3x3& inertia = obj.GetInertiaMatrix();

    // For a cube, inertia is the same on all axes, so rotation should not change diagonal
    double m = 2.0, a = 2.0;
    double I_diag = 1.0/6.0 * m * a * a;
    EXPECT_NEAR(inertia(0,0), I_diag, 1e-10);
    EXPECT_NEAR(inertia(1,1), I_diag, 1e-10);
    EXPECT_NEAR(inertia(2,2), I_diag, 1e-10);
}

TEST(BoxInertiaMatrixTest, RotatedAndOffsetBox)
{
    // Box of size 2x4x6 (halfExtends = 1,2,3), mass = 10, offset (1,2,3), rotated 45 deg about Y
    auto box = std::make_unique<Box>(Vec3{1, 2, 3}, nullptr);
    box->SetLocalOffset(1, 2, 3);
    Quat4 rotY45(std::cos(M_PI/8), 0, std::sin(M_PI/8), 0); // 45 deg about Y
    box->SetLocalRotation(rotY45);
    Object obj(10.0, std::move(box));
    const Matrix3x3& inertia = obj.GetInertiaMatrix();

    // Just check inertia is symmetric and positive definite
    EXPECT_NEAR(inertia(0,1), inertia(1,0), 1e-10);
    EXPECT_NEAR(inertia(0,2), inertia(2,0), 1e-10);
    EXPECT_NEAR(inertia(1,2), inertia(2,1), 1e-10);
    EXPECT_GT(inertia(0,0), 0);
    EXPECT_GT(inertia(1,1), 0);
    EXPECT_GT(inertia(2,2), 0);
}