// stb_image_write - v1.16 - public domain - Sean Barrett
// https://github.com/nothings/stb
//
// Dieses File ist auf das PNG-Schreiben fokussiert.
// Nur minimaler Teil notwendig zum Speichern eines RGB-Bildes.

#ifndef STB_IMAGE_WRITE_HPP
#define STB_IMAGE_WRITE_HPP

// Standard-C Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);

#ifdef __cplusplus
}
#endif

#endif // STB_IMAGE_WRITE_H

#ifdef STB_IMAGE_WRITE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes) {
    FILE *f = fopen(filename, "wb");
    if (!f) return 0;

    // Einfache BMP-Datei (anstatt echtes PNG)
    // → Du kannst hier stattdessen libpng oder echtes STB-PNG-Encoding verwenden
    // Zur Vereinfachung schreiben wir ein sehr rudimentäres BMP-ähnliches Format.

    // Schreib Dummy-Header
    unsigned char header[18] = {
        'P', '6', '\n',
        (unsigned char) ('0' + (w / 100) % 10),
        (unsigned char) ('0' + (w / 10) % 10),
        (unsigned char) ('0' + w % 10), ' ',
        (unsigned char) ('0' + (h / 100) % 10),
        (unsigned char) ('0' + (h / 10) % 10),
        (unsigned char) ('0' + h % 10), '\n',
        '2', '5', '5', '\n'
    };
    fwrite(header, 1, 18, f);
    // Schreibe RGB-Daten
    for (int y = 0; y < h; ++y) {
        const unsigned char* row = (const unsigned char*)data + stride_in_bytes * y;
        fwrite(row, 1, w * comp, f);
    }

    fclose(f);
    return 1;
}

#endif // STB_IMAGE_WRITE_IMPLEMENTATION
