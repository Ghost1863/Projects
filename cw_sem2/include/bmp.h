#include "structures.h"

#ifndef BMP_H
#define BMP_H

BMPFile* read_bmp(char file_name[]); 

void write_bmp(char file_name[],BMPFile* bmpf);

void print_file_header(BMPHeader header);

void print_info_header(DIBHeader header);

void free_bmpfile(BMPFile* bmpf);

#endif

