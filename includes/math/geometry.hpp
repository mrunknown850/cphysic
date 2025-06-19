#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include "object.hpp"
#include "vectors.hpp"
#include "quaternions.hpp"

// class Object;

enum class GeometryType
{
    BOX
};

class Geometry
{
protected:
    Vec3 offset;
    Quat4 rotation;
    Object *object;

public:
    Geometry(Object *obj) : offset(Vec3()), rotation(Quat4()), object(obj) {}

    virtual GeometryType GetType() const = 0;
    virtual bool CollidesWith(const Geometry &other) const = 0;
    virtual std::vector<Vec3> GetNormalAxis() const = 0;

    const Vec3 &GetLocalOffset() const { return offset; }
    const Quat4 &GetLocalRotation() const { return rotation; }
    Vec3 GetWorldCenter() const { return offset + object->GetPosition(); }
    const Quat4 &GetWorldRotation() const { return (rotation * object->GetRotation()).Normalize(); }

    void SetLocalOffset(double _x, double _y, double _z)
    {
        this->offset.x = _x;
        this->offset.y = _y;
        this->offset.z = _z;
    }
    void SetLocalOffset(const Vec3 &new_offset)
    {
        this->offset = new_offset;
    }
    void SetLocalRotation(double _w, double _x, double _y, double _z)
    {
        this->rotation.w = _w;
        this->rotation.x = _x;
        this->rotation.y = _y;
        this->rotation.z = _z;
        this->rotation.Normalize();
    }
    void SetLocalRotation(double w, const Vec3 &axis)
    {
        this->rotation.w = w;
        this->rotation.x = axis.x;
        this->rotation.y = axis.y;
        this->rotation.z = axis.z;
        this->rotation.Normalize();
    }
    void SetLocalRotation(const Quat4 &quaternion)
    {
        this->rotation = quaternion;
        this->rotation.Normalize();
    }

    virtual ~Geometry() = default;
};

class Box : public Geometry
{
private:
    Vec3 halfExtends;

public:
    Box(Vec3 halfExtends, Object *obj) : halfExtends(halfExtends), Geometry(obj) {}

    GeometryType GetType() const override { return GeometryType::BOX; }
    bool CollidesWith(const Geometry &other) const override;

    std::vector<Vec3> GetNormalAxis() const override;

    const Vec3 &GetHalfExtends() const { return halfExtends; }
    void SetHalfExtends(double _x, double _y, double _z)
    {
        this->halfExtends.x = _x;
        this->halfExtends.y = _y;
        this->halfExtends.z = _z;
    }
    void SetHalfExtends(const Vec3 &half_extends)
    {
        this->halfExtends = half_extends;
    }
};

#endif