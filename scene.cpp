#include "Scene.hpp"
#include <vector>

Scene::~Scene() {
    for (auto obj : objects)
        delete obj;
}

void Scene::addObject(Object* obj) {
    objects.push_back(obj);
}
