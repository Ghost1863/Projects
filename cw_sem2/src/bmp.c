#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"
#include "function_params.h"
#include "errors.h"

#ifndef BMP_C
#define BMP_C

int checkBMPFormat(BMPHeader bmph){
	if (bmph.signature!=0x4d42 )
		raiseError(file_type_error,41);
}

BMPFile* readBMP(char file_name[]) {
	FILE* f=fopen(file_name,"r");
	if (!f){
		raiseError(file_opening_error,40);
	}
	BMPFile* bmp_file=(BMPFile*)malloc(sizeof(BMPFile));
	fread(&bmp_file->bmph,sizeof(BMPHeader),1,f);
	checkBMPFormat(bmp_file->bmph);
	fread(&bmp_file->dibh,sizeof(DIBHeader),1,f);

	unsigned int H = bmp_file->dibh.height;
	unsigned int W = bmp_file->dibh.width;
	bmp_file->rgb = malloc(H * sizeof(Rgb*));
	
	for(int i = 0; i < H; i++){
		bmp_file->rgb[i] = malloc(W * sizeof(Rgb) + (4 - (W * sizeof(Rgb)) % 4) % 4);
		fread(bmp_file->rgb[i], 1,W * sizeof(Rgb) + (4 - (W * sizeof(Rgb)) % 4) % 4,f);
	}
	fclose(f);
	return bmp_file;
}

void writeBMP(char file_name[],BMPFile* bmpf) {
	FILE* f = fopen(file_name, "wb");
	fwrite(&bmpf->bmph, 1, sizeof(BMPHeader), f);
	fwrite(&bmpf->dibh, 1, sizeof(DIBHeader), f);
	int H=bmpf->dibh.height;
	int W=bmpf->dibh.width;
	for (int i = 0; i < H; i++) {
		fwrite(bmpf->rgb[i], 1, W * sizeof(Rgb) + (4 - (W * sizeof(Rgb)) % 4) % 4,f);
	}
	fclose(f);
}

void freeBMPfile(BMPFile* bmpf){
	if(bmpf) {
		if(bmpf->rgb){
			for (int i = 0; i < bmpf->dibh.height; i++)
				free(bmpf->rgb[i]);
			free(bmpf->rgb);
		}
    free(bmpf);
  };
}

void printFileHeader(BMPHeader header) {
	printf("signature:\t%x (%hu)\n", header.signature,
		header.signature);
	printf("filesize:\t%x (%u)\n", header.filesize,
		header.filesize);
	printf("reserved1:\t%x (%hu)\n", header.reserved1,
		header.reserved1);
	printf("reserved2:\t%x (%hu)\n", header.reserved2,
		header.reserved2);
	printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(DIBHeader header) {
	printf("headerSize:\t%x (%u)\n", header.headerSize,
		header.headerSize);
	printf("width: \t%x (%u)\n", header.width, header.width);
	printf("height: \t%x (%u)\n", header.height,
		header.height);
	printf("planes: \t%x (%hu)\n", header.planes,
		header.planes);
	printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
	printf("compression:\t%x (%u)\n", header.compression, header.compression);
	printf("imageSize:\t%x (%u)\n", header.imageSize,header.imageSize);
	printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
	printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
	printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
	printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

void printHelp(){
	printf("Course work for option 4.3, created by Malinovskii Aleksandr.\n"
"Usage: ./program [OPTIONS] [input_file]\n\n"
"Options:\n"	
"-i, --input <filename>: Исходное изображение\n"
"-o, --outpu  <filename>: Вывод полученного изображения\n"
"-h, --help: Вывод справки\n\n"
"--rect: Рисует прямоугольник.\n"
"--left_up: Координаты левого верхнего угла прямоугольника.\n"
"--right_down: Координаты правого нижнего угла прямоугольника.\n"
"--thickness: Толщина линий прямоугольника.\n"
"--color: Цвет линий прямоугольника.\n"
"--fill: Флаг заливки прямоугольника.\n"
"--fill_color: Цвет заливки прямоугольника.\n\n"
"--ornament: Добавляет рамку в виде узора.\n"
"--pattern: Узор рамки.\n"
"--color: Цвет рамки.\n"
"--thickness: Толщина рамки.\n"
"--count: Количество элементов в рамке.\n"
"--rotate: Поворачивает изображение (или часть изображения).\n\n"
"--left_up: Координаты левого верхнего угла области поворота.\n"
"--right_down: Координаты правого нижнего угла области поворота.\n"
"--angle: Угол поворота.\n");
}
#endif