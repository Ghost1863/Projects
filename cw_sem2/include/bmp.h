#include "structures.h"

#ifndef BMP_H
#define BMP_H

BMPFile* readBMP(char file_name[]); 

int checkBMPFormat(BMPHeader bmph);

void writeBMP(char file_name[],BMPFile* bmpf);

void printFileHeader(BMPHeader header);

void printInfoHeader(DIBHeader header);

void printHelp();

void freeBMPfile(BMPFile* bmpf);

#endif

