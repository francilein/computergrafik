#pragma once
#include "object.hpp"


class MeshObject : public Object {
public:
    void loadFromFile(const std::string& filename) override;
    void normalize();
};

