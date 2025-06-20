#ifndef FORCE_HPP
#define FORCE_HPP

#include "vectors.hpp"

struct Force
{
    Vec3 offset;
    Vec3 direction;

    Force() : offset(Vec3()), direction(Vec3()) {}
    Force(Vec3 direction) : offset(Vec3()), direction(direction) {}
    Force(Vec3 offset, Vec3 direction) : offset(offset), direction(direction) {}

    Force &operator+=(const Force &other)
    {
        direction += other.direction;
        return *this;
    }
};

#endif