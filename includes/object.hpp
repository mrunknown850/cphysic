#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include "vectors.hpp"
#include "quaternions.hpp"
// #include "geometry.hpp"

class Geometry;

class Object
{
private:
    double mass;
    Quat4 rotation;
    Vec3 position;
    Vec3 velocity;

    std::unique_ptr<Geometry> geometry;

public:
    Object(double mass, Vec3 position, Quat4 rotation, std::unique_ptr<Geometry> geom)
        : mass(mass), position(position), rotation(rotation), geometry(std::move(geom)), velocity(Vec3()) {}
    
    const double &GetMass() const { return mass; }
    const Vec3 &GetVelocity() const { return velocity; }
    const Vec3 &GetPosition() const { return position; }
    const Quat4 &GetRotation() const { return rotation; }
};

#endif