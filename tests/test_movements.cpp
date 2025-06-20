// filepath: /home/MrUnknown850/Documents/cphysic/tests/test_movements.cpp
#include <gtest/gtest.h>
#include "physic/engine.hpp"
#include "physic/object.hpp"
#include "math/geometry.hpp"
#include "math/vectors.hpp"
#include <memory>

TEST(EngineTest, ObjectPositionAfterForce)
{
    std::unique_ptr<Geometry> geom = std::make_unique<Box>(Vec3(1, 1, 1), nullptr);
    Object obj(2.0, std::move(geom));

    obj.AddForce(Force{Vec3{4, 0, 0}});

    Engine engine;
    int id = engine.AddObject(std::move(obj));

    // Step the engine with dt = 1.0
    engine.Step(1.0);

    // Get the updated object
    const Object &updated = engine.GetObject(id);

    // The acceleration is F/m = (4,0,0)/2 = (2,0,0)
    // New velocity = old velocity + a*dt = (0,0,0) + (2,0,0)*1 = (2,0,0)
    // New position = old position + velocity = (0,0,0) + (2,0,0) = (2,0,0)
    EXPECT_DOUBLE_EQ(updated.GetVelocity().x, 2.0);
    EXPECT_DOUBLE_EQ(updated.GetVelocity().y, 0.0);
    EXPECT_DOUBLE_EQ(updated.GetVelocity().z, 0.0);

    EXPECT_DOUBLE_EQ(updated.GetPosition().x, 2.0);
    EXPECT_DOUBLE_EQ(updated.GetPosition().y, 0.0);
    EXPECT_DOUBLE_EQ(updated.GetPosition().z, 0.0);
}

TEST(EngineTest, MultipleForces)
{
    std::unique_ptr<Geometry> geom = std::make_unique<Box>(Vec3(1, 1, 1), nullptr);
    Object obj(1.0, std::move(geom));

    // Apply two forces: (1,0,0) and (0,2,0)
    obj.AddForce(Force{Vec3{1, 0, 0}});
    obj.AddForce(Force{Vec3{0, 2, 0}});

    Engine engine;
    int id = engine.AddObject(std::move(obj));
    engine.Step(1.0);

    const Object &updated = engine.GetObject(id);

    // Total force = (1,2,0), mass = 1, acceleration = (1,2,0)
    // New velocity = (1,2,0), new position = (1,2,0)
    EXPECT_DOUBLE_EQ(updated.GetVelocity().x, 1.0);
    EXPECT_DOUBLE_EQ(updated.GetVelocity().y, 2.0);
    EXPECT_DOUBLE_EQ(updated.GetVelocity().z, 0.0);

    EXPECT_DOUBLE_EQ(updated.GetPosition().x, 1.0);
    EXPECT_DOUBLE_EQ(updated.GetPosition().y, 2.0);
    EXPECT_DOUBLE_EQ(updated.GetPosition().z, 0.0);
}

TEST(EngineTest, NoForceNoMovement)
{
    std::unique_ptr<Geometry> geom = std::make_unique<Box>(Vec3(1, 1, 1), nullptr);
    Object obj(5.0, std::move(geom));
    obj.SetPosition(1, 2, 3);
    obj.SetVelocity(0, 0, 0);

    Engine engine;
    int id = engine.AddObject(std::move(obj));
    engine.Step(1.0);

    const Object &updated = engine.GetObject(id);

    // No force, so no movement
    EXPECT_DOUBLE_EQ(updated.GetVelocity().x, 0.0);
    EXPECT_DOUBLE_EQ(updated.GetVelocity().y, 0.0);
    EXPECT_DOUBLE_EQ(updated.GetVelocity().z, 0.0);

    EXPECT_DOUBLE_EQ(updated.GetPosition().x, 1.0);
    EXPECT_DOUBLE_EQ(updated.GetPosition().y, 2.0);
    EXPECT_DOUBLE_EQ(updated.GetPosition().z, 3.0);
}