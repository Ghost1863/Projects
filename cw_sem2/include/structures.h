#ifndef STRUCTURES_H
#define STRUCTURES_H

#pragma pack (push, 1)
//выравнивание структуры для bmp файла

typedef struct {
	unsigned short signature;			//Сигнатура файла BMP (2 байт)
	unsigned int filesize;				//Размер файла (4 байт)
	unsigned short reserved1;			//Не используется (2 байт)
	unsigned short reserved2;			//Не используется (2 байт)
	unsigned int pixelArrOffset;		//Местонахождение данных растрового массива (4 байт)
} BMPHeader;

typedef struct {
	unsigned int headerSize;			//Длина этого заголовка (4 байт)
	unsigned int width;					//Ширина изображения (4 байт)
	unsigned int height;				//Высота изображения (4 байт)
	unsigned short planes;				//Число цветовых плоскостей (2 байт)
	unsigned short bitsPerPixel;		//Бит/пиксел (2 байт)
	unsigned int compression;			//Метод сжатия (4 байт)
	unsigned int imageSize;				//Длина растрового массива (4 байт)
	unsigned int xPixelsPerMeter;		//Горизонтальное разрешение (4 байт)
	unsigned int yPixelsPerMeter;		//Вертикальное разрешение (4 байт)
	unsigned int colorsInColorTable;	//Число цветов изображения (4 байт)
	unsigned int importantColorCount;	//Число основных цветов (4 байт)
} DIBHeader;

typedef struct {
	unsigned char b;
	unsigned char g;
	unsigned char r;
} Rgb;

typedef struct{
    BMPHeader bmph;
    DIBHeader dibh;
    Rgb** rgb;
}BMPFile;

#pragma pop

typedef struct{
	char* input_file;
    char* output_file;
	int help;
	
	//rect flag
	int rect;
	int x0;
	int x1;
	int y0;
	int y1;
	int thickness;
	Rgb color;
	int fill;
	Rgb fill_color;

	//ornament flag
	int ornament;
	int pattern;
	int count;

	//rotate flag
	int rotate;
	int angle;
}FunctionParams;

#endif