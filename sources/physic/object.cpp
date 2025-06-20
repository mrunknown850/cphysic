#include "object.hpp"
#include "geometry.hpp"

void Object::SetGeometryOwner()
{
    if (geometry)
        geometry->SetOwner(this);
}
Object::~Object() = default;
