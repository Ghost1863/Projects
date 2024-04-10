#include "bmp.h"

#ifndef PROCESSING_H
#define PROCESSING_H

Rgb** draw_rectangle(FunctionParams* fp, BMPFile* bmpf);

Rgb** draw_ornament(FunctionParams* fp, BMPFile* bmpf);

Rgb** rotate_image(FunctionParams* fp,BMPFile* bmpf);

#endif