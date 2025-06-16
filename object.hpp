#pragma once
#include <vector>
#include <string>
#include "vertex.hpp"
#include "triangle.hpp"

class Object {
public:
    virtual ~Object() = default;

    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;

    virtual void loadFromFile(const std::string& filename) = 0;
};
