#include "Rasterizer.hpp"
#include <algorithm>

// Hilfsfunktion: sortiert Vertices nach y
void sortByY(Vec3& v0, Vec3& v1, Vec3& v2) {
    if (v1.y < v0.y) std::swap(v0, v1);
    if (v2.y < v0.y) std::swap(v0, v2);
    if (v2.y < v1.y) std::swap(v1, v2);
}

void drawScanline(std::vector<unsigned char>& image, int width, int height,
                  int y, int xStart, int xEnd,
                  unsigned char r, unsigned char g, unsigned char b) {
    if (y < 0 || y >= height) return;
    if (xStart > xEnd) std::swap(xStart, xEnd);
    xStart = std::max(0, xStart);
    xEnd = std::min(width - 1, xEnd);

    for (int x = xStart; x <= xEnd; ++x) {
        int index = (y * width + x) * 3;
        image[index + 0] = r;
        image[index + 1] = g;
        image[index + 2] = b;
    }
}

void drawFilledTriangle(std::vector<unsigned char>& image, int width, int height,
                        Vec3 v0, Vec3 v1, Vec3 v2, unsigned char r, unsigned char g, unsigned char b) {
    // Normale Pixelkoordinaten
    auto toPixel = [&](Vec3 v) {
        int x = static_cast<int>((v.x + 1.0f) * width / 2.0f);
        int y = static_cast<int>((v.y + 1.0f) * height / 2.0f);
        return Vec3{(float)x, (float)(height - 1 - y), 0.0f}; // invertiere Y
    };

    v0 = toPixel(v0);
    v1 = toPixel(v1);
    v2 = toPixel(v2);

    sortByY(v0, v1, v2);

    if (v1.y == v2.y) {
        // flach unten
        for (int y = (int)v0.y; y <= (int)v1.y; ++y) {
            float alpha = (float)(y - v0.y) / (v2.y - v0.y + 1e-6f);
            float beta = (float)(y - v0.y) / (v1.y - v0.y + 1e-6f);
            int xa = (int)(v0.x + (v2.x - v0.x) * alpha);
            int xb = (int)(v0.x + (v1.x - v0.x) * beta);
            drawScanline(image, width, height, y, xa, xb, r, g, b);
        }
    } else if (v0.y == v1.y) {
        // flach oben
        for (int y = (int)v0.y; y <= (int)v2.y; ++y) {
            float alpha = (float)(y - v0.y) / (v2.y - v0.y + 1e-6f);
            float beta = (float)(y - v1.y) / (v2.y - v1.y + 1e-6f);
            int xa = (int)(v0.x + (v2.x - v0.x) * alpha);
            int xb = (int)(v1.x + (v2.x - v1.x) * beta);
            drawScanline(image, width, height, y, xa, xb, r, g, b);
        }
    } else {
        // split triangle
        float alphaSplit = (v1.y - v0.y) / (v2.y - v0.y + 1e-6f);
        Vec3 vSplit = {
            v0.x + (v2.x - v0.x) * alphaSplit,
            v1.y,
            0.0f
        };
        drawFilledTriangle(image, width, height, v0, v1, vSplit, r, g, b);
        drawFilledTriangle(image, width, height, v1, vSplit, v2, r, g, b);
    }
}
