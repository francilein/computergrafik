// Sofia war hier

#include "MeshObject.hpp"
#include "ImageWriter.hpp"
#include "Rasterizer.hpp"
#include "Scene.hpp"
#include <iostream>
#include <vector>

int main() {
    const int width = 1024;
    const int height = 1024;
    std::vector<unsigned char> image(width * height * 3, 0); // Schwarz

    // Szene und Objekt
    Scene scene;
    MeshObject* obj = new MeshObject();
    obj->loadFromFile("test.obj");
    obj->normalize();

    // Normalisieren auskommentieren, da Herz schon im [-1, 1] liegt
    // obj->normalize();

    scene.addObject(obj);

    if (obj->triangles.empty()) {
        std::cerr << "Keine Dreiecke gefunden!" << std::endl;
        return 1;
    }

    int triangleCount = 0;

    auto toPixel = [&](const Vec3& v) -> Vec3 {
        float x = (v.x + 1.0f) * width / 2.0f;
        float y = (1.0f - v.y) * height / 2.0f;
        return {x, y, 0.0f};
    };

    for (const Triangle& t : obj->triangles) {
        Vec3 a = obj->vertices[t.indices[0]].position;
        Vec3 b = obj->vertices[t.indices[1]].position;
        Vec3 c = obj->vertices[t.indices[2]].position;

        std::cout << "Dreieck " << triangleCount << ": \n"
                  << "  a: (" << a.x << ", " << a.y << ")\n"
                  << "  b: (" << b.x << ", " << b.y << ")\n"
                  << "  c: (" << c.x << ", " << c.y << ")\n";

        Vec3 p0 = toPixel(a);
        Vec3 p1 = toPixel(b);
        Vec3 p2 = toPixel(c);

        drawLine(image, width, height, p0.x, p0.y, p1.x, p1.y, 255, 255, 255);
        drawLine(image, width, height, p1.x, p1.y, p2.x, p2.y, 255, 255, 255);
        drawLine(image, width, height, p2.x, p2.y, p0.x, p0.y, 255, 255, 255);

        triangleCount++;
    }

    std::cout << "Gerenderte Dreiecke: " << triangleCount << std::endl;

    // Optional: Punkte rendern (weiß)
    for (const Vertex& v : obj->vertices) {
        int x = static_cast<int>((v.position.x + 1.0f) * width / 2.0f);
        int y = static_cast<int>((1.0f - v.position.y) * height / 2.0f);

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int px = x + dx;
                int py = y + dy;
                if (px >= 0 && px < width && py >= 0 && py < height) {
                    int index = (py * width + px) * 3;
                    image[index + 0] = 255;
                    image[index + 1] = 255;
                    image[index + 2] = 255;
                }
            }
        }
    }

    ImageWriter::savePNG("debug_output.png", width, height, image);
    std::cout << "Bild gespeichert: debug_output.png\n";
    return 0;
}
