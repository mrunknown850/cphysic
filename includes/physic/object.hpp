#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <vector>
#include "force.hpp"
#include "vectors.hpp"
#include "quaternions.hpp"

class Geometry;

class Object
{
private:
    double mass;
    Quat4 rotation;
    Vec3 position;
    Vec3 velocity;

    std::vector<Force> forces;
    std::unique_ptr<Geometry> geometry;

    void SetGeometryOwner();

public:
    Object(double mass, std::unique_ptr<Geometry> geom)
        : mass(mass), position(Vec3()), rotation(Quat4()), velocity(Vec3()), geometry(std::move(geom)) { SetGeometryOwner(); }
    Object(double mass, Vec3 position, Quat4 rotation, std::unique_ptr<Geometry> geom)
        : mass(mass), position(position), rotation(rotation), geometry(std::move(geom)), velocity(Vec3()) { SetGeometryOwner(); }

    const double &GetMass() const { return mass; }
    const Vec3 &GetVelocity() const { return velocity; }
    const Vec3 &GetPosition() const { return position; }
    const Quat4 &GetRotation() const { return rotation; }
    const std::vector<Force> &GetForces() const { return forces; }

    void SetMass(double m)
    {
        this->mass = m > 0 ? m : this->mass;
    }
    void SetVelocity(double _x, double _y, double _z)
    {
        this->velocity.x = _x;
        this->velocity.y = _y;
        this->velocity.z = _z;
    }
    void SetVelocity(Vec3 &vector)
    {
        this->velocity = vector;
    }
    void SetPosition(double _x, double _y, double _z)
    {
        this->position.x = _x;
        this->position.y = _y;
        this->position.z = _z;
    }
    void SetPosition(Vec3 &vector)
    {
        this->position = vector;
    }
    void SetRotation(double _w, double _x, double _y, double _z)
    {
        this->rotation.w = _w;
        this->rotation.x = _x;
        this->rotation.y = _y;
        this->rotation.z = _z;
        this->rotation.Normalize();
    }
    void SetRotation(double w, const Vec3 &axis)
    {
        this->rotation.w = w;
        this->rotation.x = axis.x;
        this->rotation.y = axis.y;
        this->rotation.z = axis.z;
        this->rotation.Normalize();
    }
    void SetRotation(const Quat4 &quaternion)
    {
        this->rotation = quaternion;
        this->rotation.Normalize();
    }

    void AddForce(const Force &f)
    {
        forces.emplace_back(f);
    }
    void ClearForces()
    {
        forces.clear();
    }

    // Move constructor
    Object(Object &&) noexcept = default;
    // Move assignment
    Object &operator=(Object &&) noexcept = default;

    // Delete copy constructor and copy assignment
    Object(const Object &) = delete;
    Object &operator=(const Object &) = delete;

    ~Object();
};

#include "geometry.hpp"

#endif