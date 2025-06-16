#pragma once
#include <vector>
#include "Vec3.hpp"

void drawLine(std::vector<unsigned char>& image, int width, int height,
              int x0, int y0, int x1, int y1,
              unsigned char r, unsigned char g, unsigned char b);
