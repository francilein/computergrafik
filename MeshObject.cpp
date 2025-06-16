#include "MeshObject.hpp"
#include <fstream>
#include <sstream>
#include <algorithm> 

void MeshObject::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            Vertex v;
            ss >> v.position.x >> v.position.y >> v.position.z;
            v.color = {1.0f, 1.0f, 1.0f};  // default weiß
            vertices.push_back(v);
        } else if (prefix == "f") {
            unsigned int i1, i2, i3;
            ss >> i1 >> i2 >> i3;
            triangles.push_back({{i1 - 1, i2 - 1, i3 - 1}});
        }
    }
}

void MeshObject::normalize() {
    if (vertices.empty()) return;

    Vec3 min = vertices[0].position;
    Vec3 max = vertices[0].position;

    for (const auto& v : vertices) {
        min.x = std::min(min.x, v.position.x);
        min.y = std::min(min.y, v.position.y);
        min.z = std::min(min.z, v.position.z);

        max.x = std::max(max.x, v.position.x);
        max.y = std::max(max.y, v.position.y);
        max.z = std::max(max.z, v.position.z);
    }

    Vec3 center = {
        (min.x + max.x) / 2.0f,
        (min.y + max.y) / 2.0f,
        (min.z + max.z) / 2.0f
    };
    float scale = std::max({ max.x - min.x, max.y - min.y, max.z - min.z }) / 2.0f;
    if (scale == 0.0f) scale = 1.0f;

    for (auto& v : vertices) {
        v.position.x = (v.position.x - center.x) / scale;
        v.position.y = (v.position.y - center.y) / scale;
        v.position.z = (v.position.z - center.z) / scale;
    }
}
