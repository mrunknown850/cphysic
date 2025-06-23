#include <gtest/gtest.h>
#include "vectors.hpp"

TEST(Vec4Test, DefaultConstructor) {
    Vec4 v;
    EXPECT_DOUBLE_EQ(v.x, 0);
    EXPECT_DOUBLE_EQ(v.y, 0);
    EXPECT_DOUBLE_EQ(v.z, 0);
    EXPECT_DOUBLE_EQ(v.w, 0);
}

TEST(Vec4Test, ParameterizedConstructor) {
    Vec4 v(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.w, 1.0);
    EXPECT_DOUBLE_EQ(v.x, 2.0);
    EXPECT_DOUBLE_EQ(v.y, 3.0);
    EXPECT_DOUBLE_EQ(v.z, 4.0);
    
}

TEST(Vec4Test, Addition) {
    Vec4 v1(0, 1, 2, 3);
    Vec4 v2(4, 5, 6, 7);
    Vec4 v3 = v1 + v2;
    EXPECT_DOUBLE_EQ(v3.w, 4);
    EXPECT_DOUBLE_EQ(v3.x, 6);
    EXPECT_DOUBLE_EQ(v3.y, 8);
    EXPECT_DOUBLE_EQ(v3.z, 10);
}

TEST(Vec4Test, Subtraction) {
    Vec4 v1(4, 5, 6, 7);
    Vec4 v2(0, 1, 2, 3);
    Vec4 v3 = v1 - v2;
    EXPECT_DOUBLE_EQ(v3.w, 4);
    EXPECT_DOUBLE_EQ(v3.x, 4);
    EXPECT_DOUBLE_EQ(v3.y, 4);
    EXPECT_DOUBLE_EQ(v3.z, 4);
}

TEST(Vec4Test, ScalarMultiplication) {
    Vec4 v(1, 2, 3, 4);
    Vec4 result = v * 2.0;
    EXPECT_DOUBLE_EQ(result.w, 2);
    EXPECT_DOUBLE_EQ(result.x, 4);
    EXPECT_DOUBLE_EQ(result.y, 6);
    EXPECT_DOUBLE_EQ(result.z, 8);
}

TEST(Vec4Test, ScalarDivision) {
    Vec4 v(2, 4, 6, 8);
    Vec4 result = v / 2.0;
    EXPECT_DOUBLE_EQ(result.w, 1);
    EXPECT_DOUBLE_EQ(result.x, 2);
    EXPECT_DOUBLE_EQ(result.y, 3);
    EXPECT_DOUBLE_EQ(result.z, 4);
}

TEST(Vec4Test, DotProduct) {
    Vec4 v1(1, 2, 3, 4);
    Vec4 v2(4, -5, 6, -7);
    double dot = v1 * v2;
    EXPECT_DOUBLE_EQ(dot, -16);
}

TEST(Vec4Test, Normalize) {
    Vec4 v(3, 0, 4, 0);
    v.Normalize();
    EXPECT_NEAR(v.w, 0.6, 1e-9);
    EXPECT_NEAR(v.x, 0.0, 1e-9);
    EXPECT_NEAR(v.y, 0.8, 1e-9);
    EXPECT_NEAR(v.z, 0.0, 1e-9);
}

TEST(Vec4Test, Equality) {
    Vec4 v1(1, 2, 3, 5);
    Vec4 v2(1, 2, 3, 5);
    EXPECT_TRUE(v1 == v2);
}

TEST(Vec4Test, Inequality) {
    Vec4 v1(1, 2, 3, 0);
    Vec4 v2(3, 2, 1, 0);
    EXPECT_FALSE(v1 == v2);
}