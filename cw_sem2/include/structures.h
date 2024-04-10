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
	//rect flag
	int rect;
	int rect_left;
	int rect_up;
	int rect_right;
	int rect_down;
	int rect_thickness;
	Rgb rect_color;
	int rect_fill;
	Rgb rect_fill_color;

	//ornament flag
	int ornament;
	int ornament_pattern;
	Rgb ornament_color;
	int ornament_thickness;
	int ornament_count;

	//rotate flag
	int rotate;
	int rotate_left;
	int rotate_up;
	int rotate_right;
	int rotate_down;
	int rotate_angle;
}FunctionParams;

#endif