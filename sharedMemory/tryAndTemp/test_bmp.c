#include <stdio.h>
#include <stdlib.h>
int main() {

    int width = 20;           // Keep these in variables, since
    int height = 20;          // they'll change later.

    char tag[] = { 'B', 'M' };
    int header[] = {
        0x3a, 0x00, 0x36,
        0x28,                // Header Size
        width, height,       // Image dimensions in pixels
        0x180001,            // 24 bits/pixel, 1 color plane
        0,                   // BI_RGB no compression
        0,                   // Pixel data size in bytes
        0x002e23, 0x002e23,  // Print resolution
        0, 0,                // No color palette
    };

    FILE *fp = fopen("test.bmp", "w+");
    fwrite(&tag, sizeof(tag), 1, fp);
    fwrite(&header, sizeof(header), 1, fp);
    fclose(fp);
}