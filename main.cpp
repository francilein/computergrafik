#include "MeshObject.hpp"
#include "ImageWriter.hpp"
#include "Rasterizer.hpp"
#include <iostream>
#include <vector>

int main() {
    const int width = 1024;
    const int height = 1024;
    std::vector<unsigned char> image(width * height * 3, 0); // Schwarz

    // Mesh laden
    MeshObject obj;
    obj.loadFromFile("test.obj");
    obj.normalize();

    // Prüfe ob genug Dreiecke vorhanden sind
    if (obj.triangles.empty()) {
        std::cerr << "Keine Dreiecke gefunden!" << std::endl;
        return 1;
    }

    // Nur erstes Dreieck zeichnen
    auto t = obj.triangles[0];
    Vec3 a = obj.vertices[t.indices[0]].position;
    Vec3 b = obj.vertices[t.indices[1]].position;
    Vec3 c = obj.vertices[t.indices[2]].position;

    std::cout << "a: (" << a.x << ", " << a.y << ")\n";
    std::cout << "b: (" << b.x << ", " << b.y << ")\n";
    std::cout << "c: (" << c.x << ", " << c.y << ")\n";

    drawFilledTriangle(image, width, height, a, b, c, 255, 0, 0);

    ImageWriter::savePNG("debug_output.png", width, height, image);
    std::cout << "Bild gespeichert: debug_output.png\n";
    return 0;
}
