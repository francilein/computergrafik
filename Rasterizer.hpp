#pragma once
#include <vector>
#include "Vec3.hpp"

void drawFilledTriangle(std::vector<unsigned char>& image, int width, int height,
                        Vec3 v0, Vec3 v1, Vec3 v2, unsigned char r, unsigned char g, unsigned char b);
