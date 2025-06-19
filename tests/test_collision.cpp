#include <gtest/gtest.h>
#include "geometry.hpp"
#include "object.hpp"


Object obj1(1, Vec3(), Quat4(), nullptr);
Object obj2(1, Vec3(), Quat4(), nullptr);

TEST(BoxBoxCollision, OverlappingBoxes) {
    Box b1(Vec3(1, 1, 1), &obj1);
    Box b2(Vec3(1, 1, 1), &obj2);

    // Both at origin
    EXPECT_TRUE(b1.CollidesWith(b2));
}

TEST(BoxBoxCollision, NonOverlappingBoxes) {
    Box b1(Vec3(1, 1, 1), &obj1);
    Box b2(Vec3(1, 1, 1), &obj2);

    b1.SetLocalOffset(5, 0, 0);
    EXPECT_FALSE(b1.CollidesWith(b2));
}

TEST(BoxBoxCollision, TouchingBoxes) {
    Box b1(Vec3(1, 1, 1), &obj1);
    Box b2(Vec3(1, 1, 1), &obj2);

    b2.SetLocalOffset(2, 0, 0);
    EXPECT_TRUE(b1.CollidesWith(b2));
}

TEST(BoxBoxCollision, RotatedBoxes) {
    Box b1(Vec3(1, 1, 1), &obj1);
    Box b2(Vec3(1, 1, 1), &obj2);

    b2.SetLocalRotation(M_PI / 4, 0, 0, 1);
    EXPECT_TRUE(b1.CollidesWith(b2));
}

TEST(BoxBoxCollision, DegenerateBox) {
    Box b1(Vec3(1, 1, 0), &obj1); // Flat in Z
    Box b2(Vec3(1, 1, 1), &obj2);

    EXPECT_TRUE(b1.CollidesWith(b2));
}
