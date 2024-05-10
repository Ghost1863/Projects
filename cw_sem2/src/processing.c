#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include <errors.h>
#include "processing.h"
#include "bmp.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#ifndef PROCESSING_C
#define PROCESSING_C

int check(int x, int y, int W, int H)
{
    return x >= 0 && x < W && y >= 0 && y < H;
}

void drawSimpleCircle(BMPFile* bmpf,int x0, int y0, int radius, Rgb color){
    int D = 3 - 2 * radius;
    int x = 0;
    int y = radius;
	int W=bmpf->dibh.width;
	int H=bmpf->dibh.height;
    while (x <= y) {
		if (check(x+x0,y+y0,W,H))
        	bmpf->rgb[y+y0][x+x0]=color;
		
		if (check(y+x0,x+y0,W,H))
			bmpf->rgb[x+y0][y+x0]=color;
        
		if (check(-y+x0,x+y0,W,H))
			bmpf->rgb[x+y0][-y+x0 ]=color;
		
		if (check(y+y0,-x+x0,W,H))
        	bmpf->rgb[y+y0][-x+x0]=color;
		
		if (check(-y+y0,-x+x0,W,H))
        	bmpf->rgb[-y+y0][-x+x0]=color;
		
		if (check(-y+x0,-x+y0,W,H))
       		bmpf->rgb[-x+y0][-y+x0]=color;
		
		if (check(y+x0,-x+y0,W,H))
        	bmpf->rgb[-x+y0][y+x0]=color;
		
		if (check(x+x0,-y+y0,W,H))
        	bmpf->rgb[-y+y0][x+x0]=color;
        
		if (D < 0) {
            D += 4 * x + 6;
            x++;
        } else {
            D += 4 * (x - y) + 10;
            x++;
            y--;
        }
    }
}

void drawLine(BMPFile* bmpf, int x1, int y1, int x2, int y2, int line_thickness, Rgb color){
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    int h = bmpf->dibh.height;
    int w = bmpf->dibh.width;
    while(1){
        if (y1 >= 0 && y1 <= h && x1 >= 0 && x1 <= w){
            if (line_thickness == 1){
				bmpf->rgb[y1][x1]=color;
            }   
        }

        if(line_thickness > 1 && x1 - (line_thickness/2) < w && y1 - (line_thickness/2) < h && x1 + (line_thickness/2) >= 0 && y1 + (line_thickness/2) >= 0){
            drawSimpleCircle(bmpf, x1, y1, line_thickness/2 ,color);
        }

        if (x1 == x2 && y1 == y2){
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


Rgb** drawRectangle(FunctionParams* fp,BMPFile* bmpf){
	int x0=min(fp->x0,fp->x1);
	int x1=max(fp->x0,fp->x1);
	int y0=min(fp->y0,fp->y1);
	int y1=max(fp->y0,fp->y1);
	
	y0 = bmpf->dibh.height-y0-1;
	y1 = bmpf->dibh.height-y1-1;

	drawLine(bmpf, x0, y0, x1, y0, fp->thickness, fp->color);
    drawLine(bmpf, x0, y1, x1, y1, fp->thickness, fp->color);
    drawLine(bmpf, x1, y1, x1, y0, fp->thickness, fp->color);
    drawLine(bmpf, x0, y1, x0, y0, fp->thickness, fp->color);
	
	printf("y0: %d y1:%d",y0,y1);
	printf("x0: %d x1:%d",x0,x1);
	if (fp->fill){

			for (int i = y1+fp->thickness/2; i <= y0-fp->thickness/2; i++) {
				for (int j = x0+fp->thickness/2; j <= x1-fp->thickness/2; j++){
					if (check(j,i,bmpf->dibh.width,bmpf->dibh.height))
						bmpf->rgb[i][j]=fp->fill_color;
					}		
			}
		}
	return bmpf->rgb;
}

Rgb** drawOrnament(FunctionParams* fp, BMPFile* bmpf){

	switch (fp->pattern)
	{
	case 1://pattern rectangle
	{
		int down_border=0;
		int left_border=0;
		int up_border=bmpf->dibh.height-1;
		int right_border=bmpf->dibh.width-1;

		for (int l = 0; l < fp->count; l++){
			for (int k=0;k<fp->thickness;k++){
				for (int i = down_border; i <= up_border; i++) {
					for (int j = left_border; j <=right_border ; j++){
						if(i==down_border|| i==up_border || j==left_border||j==right_border){
							bmpf->rgb[i][j]=fp->color;
						}
					}
				}
				down_border+=1;
				up_border-=1;
				left_border+=1;
				right_border-=1;
			}
		down_border+=fp->thickness;
		up_border-=fp->thickness;
		left_border+=fp->thickness;
		right_border-=fp->thickness;
		}
	}
		break;
	case 2://pattern circle
	{
	int centerX = bmpf->dibh.width / 2;
    int centerY = bmpf->dibh.height / 2;
    int radius = (centerX <centerY) ? centerX : centerY;
	
	for (int i = 0; i < bmpf->dibh.height; i++) {
            for (int j = 0; j < bmpf->dibh.width; j++) {
                double distance = sqrt(pow((j - centerX),2) + pow((i - centerY),2));
                if (distance > radius) 
					bmpf->rgb[i][j]=fp->color;
            }
	}
		break;
	}
	case 3://pattern semicircle
	{
		double width = (double)(bmpf->dibh.width - fp->count * fp->thickness) / (fp->count * 2);
        double height = (double)(bmpf->dibh.height - fp->count * fp->thickness) / (fp->count * 2);
        int radiusX = ceil(width);
        int radiusY = ceil(height);

        int count = 0;
        int middleX[fp->count * 4];
        int middleY[fp->count * 4];

        //Верхние координаты
        int current =  fp->thickness / 2 + radiusX + 1;
        for (int i = 0; i < fp->count; ++i) {
            middleX[count] = current;
            middleY[count++] = 0;
            current += radiusX + fp->thickness + radiusX;
        }

        //Левые координаты
        current = fp->thickness / 2 + radiusY + 1;
        for (int i = 0; i < fp->count; ++i) {
            middleX[count] = 0;
            middleY[count++] = current;
            current += radiusY + fp->thickness + radiusY;
        }

        //Правые координаты
        current = fp->thickness / 2 + radiusY - 1;
        for (int i = 0; i < fp->count; ++i) {
            middleX[count] = bmpf->dibh.width - 1;
            middleY[count++] = current;
            current += radiusY + fp->thickness + radiusY;
        }

        //Нижние координаты
        current = fp->thickness / 2 + radiusX - 1;
        for (int i = 0; i < fp->count; ++i) {
            middleX[count] = current;
            middleY[count++] = bmpf->dibh.height - 1;
            current += radiusX + fp->thickness + radiusX;
        }

        for (int y = 0; y < bmpf->dibh.height; ++y) {

            for (int x = 0 ; x < bmpf->dibh.width; ++x) {
                
                for (int i = 0; i < fp->count*4; ++i) {
                    int length = sqrt(pow(x - middleX[i], 2) + pow(y - middleY[i], 2));
                    if ((middleX[i] == 0 || middleX[i] == bmpf->dibh.width - 1) && length > radiusY && length < radiusY + fp->thickness) {
						bmpf->rgb[y][x]=fp->color;
                    }
                    
                    if ((middleY[i] == 0 || middleY[i] == bmpf->dibh.height - 1) && length > radiusX && length < radiusX + fp->thickness) {
                        bmpf->rgb[y][x]=fp->color;
                    }
                }
            }
        }
		break;
	}

	default:
		break;
	}

	return bmpf->rgb;
}

void swapPixels(Rgb* a, Rgb* b){
	Rgb temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

Rgb** rotateImage(FunctionParams* fp,BMPFile* bmpf){
		
		int H=bmpf->dibh.height;
		int W=bmpf->dibh.width;
		
		int area_H = max(fp->y0,fp->y1) - min(fp->y0,fp->y1);
    	int area_W = max(fp->x0,fp->x1) - min(fp->x0,fp->x1);

		int centerX = (fp->x0 +fp->x1) / 2;
		int centerY = (fp->y0+fp->y1) / 2;

		int start_x = centerX - area_H / 2;
    	int start_y = H - (centerY - area_W / 2) - 1;
		
		
		fp->y0 = H-fp->y0-1;
		fp->y1 = H-fp->y1-1;
		int y0=max(fp->y0,fp->y1);
		int y1=min(fp->y0,fp->y1);
		int x0=min(fp->x0,fp->x1);
		int x1=max(fp->x0,fp->x1);
		
		Rgb black={0,0,0};
		Rgb **area = malloc(sizeof( Rgb *) * (area_H ));
		for (int i = 0; i <  area_H ; i++)
		{
			area[i] = malloc(sizeof( Rgb) * (area_W));
			for (int j = 0; j < area_W; j++)
			{		
				area[i][j] = bmpf->rgb[i + y1+1][j + x0];
				//bmpf->rgb[i + y1+1][j + x0]=black;
			}
		}
		switch (fp->angle)
		{
		case 90:
			for (int y = 0; y < area_W; y ++) {
                for (int x = 0; x < area_H; x ++) {
					if(start_y - (area_W - y - 1)<H
					 && start_y - (area_W - y - 1)>=0
					  &&  start_x + (area_H - x - 1)>=0
					   &&  start_x + (area_H - x - 1)<W)
					bmpf->rgb[start_y - (area_W - y - 1)][ start_x + (area_H - x - 1)]=area[x][y];
                }
            }
			break;
		case 180:
			for (int y = y0; y > y1; y --) {
            	for (int x = x0; x < x1; x ++) {
					bmpf->rgb[y][x]=area[(y0 - y)][area_W - (x - x0) - 1];
            }
        }
			break;
		case 270:
			  for (int y = 0; y < area_W; y ++) {
                    for (int x = 0; x < area_H; x ++) {
						if(start_y-y<H && start_y-y>=0 && start_x + x>=0 && start_x + x<W)
						bmpf->rgb[start_y - y][start_x + x]=area[x][y];
                }
			  }
			break;
		default:
			break;
		}
		
		/*for (int i = RightY; i < LeftY; i++)
		{
			for (int j = LeftX; j < RightX; j++)
			{
				int X = round((j - centerX) * cos(ang) - (i - centerY) * sin(ang) + centerX),
					Y = round((j - centerX) * sin(ang) + (i - centerY) * cos(ang) + centerY);
				
				if(Y<H && Y>=0 && X>=0 && X<W)
					bmpf->rgb[Y][X]=area[i - RightY][j - LeftX];
			}
		}
	*/

	for (int i = 0; i < (y0 - y1); i++)
	{
		free(area[i]);
	}
	free(area);
		
	return bmpf->rgb;
}

#endif
