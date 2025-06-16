#include "Scene.hpp"
#include "MeshObject.hpp"
#include "ImageWriter.hpp"
#include "Rasterizer.hpp"

#include <iostream>

int main() {
    const int width = 1024;
    const int height = 1024;
    const int pointSize = 5; // Quadratgröße für jeden Punkt

    std::vector<unsigned char> image(width * height * 3, 0); // RGB schwarz

    Scene scene;
    MeshObject* obj = new MeshObject();
    obj->loadFromFile("test.obj");
    obj->normalize();
    scene.addObject(obj);

    int totalPixelsSet = 0;

    for (Object* object : scene.objects) {
        for (const Vertex& v : object->vertices) {
            int x = static_cast<int>((v.position.x + 1.0f) * width / 2.0f);
            int y = static_cast<int>((v.position.y + 1.0f) * height / 2.0f);
            y = height - 1 - y; // y invertieren (Bild oben links = 0,0)

            // Punktgröße: Quadrat zeichnen
            for (Object* object : scene.objects) {
                for (const Triangle& t : object->triangles) {
                    Vec3 a = object->vertices[t.indices[0]].position;
                    Vec3 b = object->vertices[t.indices[1]].position;
                    Vec3 c = object->vertices[t.indices[2]].position;

                    drawFilledTriangle(image, width, height, a, b, c, 255, 0, 0); // rot z. B.
                }
            }           

        }
    }

    std::cout << "Gesetzte Pixel: " << totalPixelsSet << std::endl;
    ImageWriter::savePNG("output.png", width, height, image);
    std::cout << "Bild gespeichert: output.png" << std::endl;

    return 0;
}
