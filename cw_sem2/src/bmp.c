#include <getopt.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

#ifndef BMP_C
#define BMP_C

BMPFile* read_bmp(char file_name[]) {
	FILE* f=fopen(file_name,"r");
	if (!f){
		printf("can't open file");
	}
	BMPFile* bmp_file=(BMPFile*)malloc(sizeof(BMPFile));
	fread(&bmp_file->bmph,sizeof(BMPHeader),1,f);
	fread(&bmp_file->dibh,sizeof(DIBHeader),1,f);

	unsigned int H = bmp_file->dibh.height;
	unsigned int W = bmp_file->dibh.width;
	bmp_file->rgb = malloc(H * sizeof(Rgb*));
	
	for(int i = 0; i < H; i++){
		bmp_file->rgb[i] = malloc(W * sizeof(Rgb) + (W * 3) % 4);
		fread(bmp_file->rgb[i], 1, W * sizeof(Rgb) + (W * 3) % 4,f);
	}
	fclose(f);
	return bmp_file;
}

void write_bmp(char file_name[],BMPFile* bmpf) {
	FILE* f = fopen(file_name, "wb");
	fwrite(&bmpf->bmph, 1, sizeof(BMPHeader), f);
	fwrite(&bmpf->dibh, 1, sizeof(DIBHeader), f);
	int H=bmpf->dibh.height;
	int W=bmpf->dibh.width;
	for (int i = 0; i < H; i++) {
		fwrite(bmpf->rgb[i], 1, W * sizeof(Rgb) + (W * 3) % 4,f);
	}
	fclose(f);
}

void free_bmpfile(BMPFile* bmpf){
	if(bmpf) {
		if(bmpf->rgb){
			for (int i = 0; i < bmpf->dibh.height; i++)
				free(bmpf->rgb[i]);
			free(bmpf->rgb);
		}
    free(bmpf);
  };
}

void print_file_header(BMPHeader header) {
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

void print_info_header(DIBHeader header) {
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

#endif