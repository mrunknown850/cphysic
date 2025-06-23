#include <gtest/gtest.h>
#include "quaternions.hpp"

TEST(Quat4Test, DefaultConstructor)
{
    Quat4 a;
    EXPECT_DOUBLE_EQ(a.w, 1);
    EXPECT_DOUBLE_EQ(a.x, 0);
    EXPECT_DOUBLE_EQ(a.y, 0);
    EXPECT_DOUBLE_EQ(a.z, 0);
}

TEST(Quat4Test, AxisConstructor)
{
    Quat4 a = Quat4(3, Vec3(4, 12, 84));
    EXPECT_NEAR(a.w, 3.0 / 85.0, 1e-9);
    EXPECT_NEAR(a.x, 4.0 / 85.0, 1e-9);
    EXPECT_NEAR(a.y, 12.0 / 85.0, 1e-9);
    EXPECT_NEAR(a.z, 84.0 / 85.0, 1e-9);
}

TEST(Quat4Test, ParameterizedConstructor)
{
    Quat4 a = Quat4(3, 4, 12, 84);
    EXPECT_NEAR(a.w, 3.0 / 85.0, 1e-9);
    EXPECT_NEAR(a.x, 4.0 / 85.0, 1e-9);
    EXPECT_NEAR(a.y, 12.0 / 85.0, 1e-9);
    EXPECT_NEAR(a.z, 84.0 / 85.0, 1e-9);
}

TEST(Quat4Test, Inverse)
{
    Quat4 a = -Quat4(69, -5, 4, -5);
    Quat4 b = Quat4(69, 5, -4, 5);
    EXPECT_DOUBLE_EQ(a.w, b.w);
    EXPECT_DOUBLE_EQ(a.x, b.x);
    EXPECT_DOUBLE_EQ(a.y, b.y);
    EXPECT_DOUBLE_EQ(a.z, b.z);
}

TEST(Quat4Test, Addition)
{
    Quat4 a(1, 2, 3, 4);
    Quat4 b(5, 6, 7, 8);
    Quat4 c = a + b;
    EXPECT_DOUBLE_EQ(c.w, a.w + b.w);
    EXPECT_DOUBLE_EQ(c.x, a.x + b.x);
    EXPECT_DOUBLE_EQ(c.y, a.y + b.y);
    EXPECT_DOUBLE_EQ(c.z, a.z + b.z);
}

TEST(Quat4Test, Multiplication)
{
    Quat4 a(1, 0, 1, 0);
    Quat4 b(1, 0.5, 0.5, 0.75);
    Quat4 c = a * b;
    // Manually compute expected result
    double w = a.w * b.w - (a.x * b.x + a.y * b.y + a.z * b.z);
    double x = a.w * b.x + b.w * a.x + (a.y * b.z - a.z * b.y);
    double y = a.w * b.y + b.w * a.y + (a.z * b.x - a.x * b.z);
    double z = a.w * b.z + b.w * a.z + (a.x * b.y - a.y * b.x);
    EXPECT_NEAR(c.w, w, 1e-9);
    EXPECT_NEAR(c.x, x, 1e-9);
    EXPECT_NEAR(c.y, y, 1e-9);
    EXPECT_NEAR(c.z, z, 1e-9);
}

TEST(Quat4Test, Normalize)
{
    Quat4 a(0, 3, 4, 0);
    a.Normalize();
    double norm = std::sqrt(0 * 0 + 3 * 3 + 4 * 4 + 0 * 0);
    EXPECT_NEAR(a.w, 0.0, 1e-9);
    EXPECT_NEAR(a.x, 3.0 / norm, 1e-9);
    EXPECT_NEAR(a.y, 4.0 / norm, 1e-9);
    EXPECT_NEAR(a.z, 0.0, 1e-9);
}

TEST(Quat4Test, Rotation)
{
    Vec3 a = Vec3(1, 0, 0);
    Quat4 r = Quat4(1, 0, 1, 0);
    a = a * r;
    EXPECT_DOUBLE_EQ(a.x, 0);
    EXPECT_DOUBLE_EQ(a.y, 0);
    EXPECT_DOUBLE_EQ(a.z, -1);
}