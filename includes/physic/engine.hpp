#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "object.hpp"
#include "config.hpp"
#include <vector>
class Engine
{
private:
    std::vector<Object> objectList;

public:
    // Getting
    const Object &GetObject(int id) const
    {
        return objectList[id];
    }

    // Adding
    int AddObject(Object obj); // Change signature to take by value
    void Step(double dt = 1.0 / FPS);
};

#endif