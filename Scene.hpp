#pragma once

#include <vector>
#include "object.hpp"   // ← wichtig: korrekter Dateiname!

class Scene {
public:
    std::vector<Object*> objects;

    ~Scene();
    void addObject(Object* obj);
};
