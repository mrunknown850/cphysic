#include <gtest/gtest.h>
#include "math/geometry.hpp"
#include "physic/object.hpp"

Object obj0(1.0, nullptr);
Object obj9(1.0, nullptr);

TEST(SphereBoxCollisionTest, SphereInsideBox)
{
    Box box(Vec3{2, 2, 2}, &obj0);
    box.SetLocalOffset(0, 0, 0);

    Sphere sphere(1.0, &obj9);
    sphere.SetLocalOffset(0, 0, 0);

    EXPECT_TRUE(sphere.CollidesWith(box));
    EXPECT_TRUE(box.CollidesWith(sphere));
}

TEST(SphereBoxCollisionTest, SphereTouchingBoxSurface)
{
    Box box(Vec3{1, 1, 1}, &obj0);
    box.SetLocalOffset(0, 0, 0);

    Sphere sphere(1.0, &obj9);
    sphere.SetLocalOffset(2, 0, 0);

    EXPECT_TRUE(sphere.CollidesWith(box));
    EXPECT_TRUE(box.CollidesWith(sphere));
}

TEST(SphereBoxCollisionTest, SphereOutsideBoxNoCollision)
{
    Box box(Vec3{1, 1, 1}, &obj0);
    box.SetLocalOffset(0, 0, 0);

    Sphere sphere(1.0, &obj9);
    sphere.SetLocalOffset(3.1, 0, 0);

    EXPECT_FALSE(sphere.CollidesWith(box));
    EXPECT_FALSE(box.CollidesWith(sphere));
}

TEST(SphereBoxCollisionTest, SphereOverlappingBoxEdge)
{
    Box box(Vec3{1, 1, 1}, &obj0);
    box.SetLocalOffset(0, 0, 0);

    Sphere sphere(1.0, &obj9);
    sphere.SetLocalOffset(1.5, 1.5, 0);

    EXPECT_TRUE(sphere.CollidesWith(box));
    EXPECT_TRUE(box.CollidesWith(sphere));
}

TEST(SphereBoxCollisionTest, BoxInsideSphere)
{
    Box box(Vec3{1, 1, 1}, &obj0);
    box.SetLocalOffset(0, 0, 0);

    Sphere sphere(10.0, &obj9);
    sphere.SetLocalOffset(0, 0, 0);

    EXPECT_TRUE(sphere.CollidesWith(box));
    EXPECT_TRUE(box.CollidesWith(sphere));
}

TEST(SphereBoxCollisionTest, SphereAndBoxFarApart)
{
    Box box(Vec3{1, 1, 1}, &obj0);
    box.SetLocalOffset(0, 0, 0);

    Sphere sphere(1.0, &obj9);
    sphere.SetLocalOffset(100, 100, 100);

    EXPECT_FALSE(sphere.CollidesWith(box));
    EXPECT_FALSE(box.CollidesWith(sphere));
}