#pragma once

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.hpp"

#include <string>
#include <vector>

class ImageWriter {
public:
    // Speichert ein RGB-Bild als PNG
    static void savePNG(const std::string& filename, int width, int height, const std::vector<unsigned char>& pixels) {
        // Kanäle = 3 (RGB), Zeilenstride = width * 3
        stbi_write_png(filename.c_str(), width, height, 3, pixels.data(), width * 3);
    }
};
