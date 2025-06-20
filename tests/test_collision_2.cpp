// sources/math/test_geometry.cpp
#include <gtest/gtest.h>
#include "math/geometry.hpp"
#include "physic/object.hpp"

Object obj(1, Vec3(), Quat4(), nullptr);

TEST(SphereCollisionTest, OverlappingSpheresCollide) {
    Sphere s1(2.0, &obj);
    s1.SetLocalOffset(0, 0, 0);
    Sphere s2(2.0, &obj);
    s2.SetLocalOffset(1, 0, 0);
    EXPECT_TRUE(s1.CollidesWith(s2));
    EXPECT_TRUE(s2.CollidesWith(s1));
}

TEST(SphereCollisionTest, TouchingSpheresCollide) {
    Sphere s1(1.0, &obj);
    s1.SetLocalOffset(0, 0, 0);
    Sphere s2(1.0, &obj);
    s2.SetLocalOffset(2, 0, 0);
    EXPECT_TRUE(s1.CollidesWith(s2));
    EXPECT_TRUE(s2.CollidesWith(s1));
}

TEST(SphereCollisionTest, SeparateSpheresDoNotCollide) {
    Sphere s1(1.0, &obj);
    s1.SetLocalOffset(0, 0, 0);
    Sphere s2(1.0, &obj);
    s2.SetLocalOffset(3, 0, 0);
    EXPECT_FALSE(s1.CollidesWith(s2));
    EXPECT_FALSE(s2.CollidesWith(s1));
}

TEST(SphereCollisionTest, DifferentRadiusCollision) {
    Sphere s1(3.0, &obj);
    s1.SetLocalOffset(0, 0, 0);
    Sphere s2(1.0, &obj);
    s2.SetLocalOffset(4, 0, 0);
    EXPECT_TRUE(s1.CollidesWith(s2));
    EXPECT_TRUE(s2.CollidesWith(s1));
}

TEST(SphereCollisionTest, ZeroRadius) {
    Sphere s1(0.0, &obj);
    s1.SetLocalOffset(0, 0, 0);
    Sphere s2(0.0, &obj);
    s2.SetLocalOffset(0, 0, 0);
    EXPECT_TRUE(s1.CollidesWith(s2));
    Sphere s3(0.0, &obj);
    s3.SetLocalOffset(1, 0, 0);
    EXPECT_FALSE(s1.CollidesWith(s3));
}