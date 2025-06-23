#include <gtest/gtest.h>
#include "vectors.hpp"
#include "matrices.hpp"

TEST(Vec3Test, DefaultConstructor)
{
    Vec3 v;
    EXPECT_DOUBLE_EQ(v.x, 0);
    EXPECT_DOUBLE_EQ(v.y, 0);
    EXPECT_DOUBLE_EQ(v.z, 0);
}

TEST(Vec3Test, ParameterizedConstructor)
{
    Vec3 v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

TEST(Vec3Test, Addition)
{
    Vec3 v1(1, 2, 3);
    Vec3 v2(4, 5, 6);
    Vec3 v3 = v1 + v2;
    EXPECT_DOUBLE_EQ(v3.x, 5);
    EXPECT_DOUBLE_EQ(v3.y, 7);
    EXPECT_DOUBLE_EQ(v3.z, 9);
}

TEST(Vec3Test, Subtraction)
{
    Vec3 v1(4, 5, 6);
    Vec3 v2(1, 2, 3);
    Vec3 v3 = v1 - v2;
    EXPECT_DOUBLE_EQ(v3.x, 3);
    EXPECT_DOUBLE_EQ(v3.y, 3);
    EXPECT_DOUBLE_EQ(v3.z, 3);
}

TEST(Vec3Test, ScalarMultiplication)
{
    Vec3 v(1, 2, 3);
    Vec3 result = v * 2.0;
    EXPECT_DOUBLE_EQ(result.x, 2);
    EXPECT_DOUBLE_EQ(result.y, 4);
    EXPECT_DOUBLE_EQ(result.z, 6);
}

TEST(Vec3Test, ScalarDivision)
{
    Vec3 v(2, 4, 6);
    Vec3 result = v / 2.0;
    EXPECT_DOUBLE_EQ(result.x, 1);
    EXPECT_DOUBLE_EQ(result.y, 2);
    EXPECT_DOUBLE_EQ(result.z, 3);
}

TEST(Vec3Test, DotProduct)
{
    Vec3 v1(1, 2, 3);
    Vec3 v2(4, -5, 6);
    double dot = v1 * v2;
    EXPECT_DOUBLE_EQ(dot, 12);
}

TEST(Vec3Test, CrossProduct)
{
    Vec3 v1(1, 0, 0);
    Vec3 v2(0, 1, 0);
    Vec3 cross = v1 ^ v2;
    EXPECT_DOUBLE_EQ(cross.x, 0);
    EXPECT_DOUBLE_EQ(cross.y, 0);
    EXPECT_DOUBLE_EQ(cross.z, 1);
}

TEST(Vec3Test, Normalize)
{
    Vec3 v(3, 0, 4);
    v.Normalize();
    EXPECT_NEAR(v.x, 0.6, 1e-9);
    EXPECT_NEAR(v.y, 0.0, 1e-9);
    EXPECT_NEAR(v.z, 0.8, 1e-9);
}

TEST(Vec3Test, Equality)
{
    Vec3 v1(1, 2, 3);
    Vec3 v2(1, 2, 3);
    EXPECT_TRUE(v1 == v2);
}

TEST(Vec3Test, Inequality)
{
    Vec3 v1(1, 2, 3);
    Vec3 v2(3, 2, 1);
    EXPECT_FALSE(v1 == v2);
}

TEST(Vec3Test, IsZero)
{
    Vec3 v1(0, 0, 0);
    Vec3 v2(1, 0, 4);
    EXPECT_TRUE(v1.IsZero());
    EXPECT_FALSE(v2.IsZero());
}

TEST(Vec3Test, SelfInverseOuterProduct)
{
    // Test with a non-zero vector
    Vec3 v(1, 2, 3);
    Matrix3x3 outer = v.SelfInverseOuter();
    // The outer product of v with itself (v * v^T) should be a 3x3 matrix:
    // [1 2 3]
    // [2 4 6]
    // [3 6 9]
    EXPECT_DOUBLE_EQ(outer(0, 0), 1);
    EXPECT_DOUBLE_EQ(outer(0, 1), 2);
    EXPECT_DOUBLE_EQ(outer(0, 2), 3);
    EXPECT_DOUBLE_EQ(outer(1, 0), 2);
    EXPECT_DOUBLE_EQ(outer(1, 1), 4);
    EXPECT_DOUBLE_EQ(outer(1, 2), 6);
    EXPECT_DOUBLE_EQ(outer(2, 0), 3);
    EXPECT_DOUBLE_EQ(outer(2, 1), 6);
    EXPECT_DOUBLE_EQ(outer(2, 2), 9);

    // Test with a zero vector
    Vec3 zero(0, 0, 0);
    Matrix3x3 zero_outer = zero.SelfInverseOuter();
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_DOUBLE_EQ(zero_outer(i, j), 0);

    // Test with negative values
    Vec3 neg(-1, -2, -3);
    Matrix3x3 neg_outer = neg.SelfInverseOuter();
    EXPECT_DOUBLE_EQ(neg_outer(0, 0), 1);
    EXPECT_DOUBLE_EQ(neg_outer(0, 1), 2);
    EXPECT_DOUBLE_EQ(neg_outer(0, 2), 3);
    EXPECT_DOUBLE_EQ(neg_outer(1, 0), 2);
    EXPECT_DOUBLE_EQ(neg_outer(1, 1), 4);
    EXPECT_DOUBLE_EQ(neg_outer(1, 2), 6);
    EXPECT_DOUBLE_EQ(neg_outer(2, 0), 3);
    EXPECT_DOUBLE_EQ(neg_outer(2, 1), 6);
    EXPECT_DOUBLE_EQ(neg_outer(2, 2), 9);
}
