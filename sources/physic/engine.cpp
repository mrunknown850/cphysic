#include "engine.hpp"

int Engine::AddObject(Object &&obj) // Take by rvalue reference
{
    objectList.emplace_back(std::move(obj)); // Move into vector
    return objectList.size() - 1;
}
void Engine::Step(double dt)
{
    Vec3 temp_vector;

    for (Object &obj : objectList)
    {
        Force accumulated_force;

        // Process motions
        for (const Force &f : obj.GetForces())
            accumulated_force += f;
        temp_vector = obj.GetVelocity() + (dt * accumulated_force.direction / obj.GetMass());
        obj.SetVelocity(temp_vector);

        // Process rotations
        // Apply force
        temp_vector = obj.GetPosition() + obj.GetVelocity();
        obj.SetPosition(temp_vector);
        obj.ClearForces();
    }
}