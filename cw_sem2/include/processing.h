#include "bmp.h"

#ifndef PROCESSING_H
#define PROCESSING_H

Rgb** drawRectangle(FunctionParams* fp, BMPFile* bmpf);

Rgb** drawOrnament(FunctionParams* fp, BMPFile* bmpf);

Rgb** rotateImage(FunctionParams* fp,BMPFile* bmpf);

Rgb** rotate(FunctionParams* fp,BMPFile* bmpf);

void swapPixels(Rgb* a, Rgb* b);

#endif