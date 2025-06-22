#include "object.hpp"
#include "geometry.hpp"

void Object::SetGeometryOwner()
{
    if (geometry)
    {
        geometry->SetOwner(this);
        inertia_matrix = geometry->GetLocalInertiaMatrix();
    }
}
Object::~Object() = default;
