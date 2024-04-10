#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include "processing.h"
#include "bmp.h"


#ifndef PROCESSING_C
#define PROCESSING_C

Rgb** draw_rectangle(FunctionParams* fp,BMPFile* bmpf){
	
	for (int k=0;k<fp->rect_thickness;k++){
		for (int i = fp->rect_down; i <= fp->rect_up; i++) {
			for (int j = fp->rect_left; j <= fp->rect_right; j++){
				if(i==fp->rect_down|| i==fp->rect_up || j==fp->rect_left||j==fp->rect_right){
					bmpf->rgb[i][j]=fp->rect_color;
				}
			}
		}
		fp->rect_down+=1;
		fp->rect_up-=1;
		fp->rect_left+=1;
		fp->rect_right-=1;
	}
	if (fp->rect_fill){
			for (int i = fp->rect_down; i <= fp->rect_up; i++) {
				for (int j = fp->rect_left; j <= fp->rect_right; j++){
						bmpf->rgb[i][j]=fp->rect_fill_color;
					}		
			}
		}

	return bmpf->rgb;
	//./CW_SEM2 --rect --left_up 300.300 --right_down 400.200 --color 0.255.0 --thickness 2 --fill --fill_color --111.222.222 ./images/Airplane.bmp
}

Rgb** draw_ornament(FunctionParams* fp, BMPFile* bmpf){
	
	int down_border=0;
	int left_border=0;
	int up_border=bmpf->dibh.height-1;
	int right_border=bmpf->dibh.width-1;

	switch (fp->ornament_pattern)
	{
	case 1://pattern rectangle
	
		for (int l = 0; l < fp->ornament_count; l++){
			for (int k=0;k<fp->ornament_thickness;k++){
				for (int i = down_border; i <= up_border; i++) {
					for (int j = left_border; j <=right_border ; j++){
						if(i==down_border|| i==up_border || j==left_border||j==right_border){
							bmpf->rgb[i][j]=fp->ornament_color;
						}
					}
				}
				down_border+=1;
				up_border-=1;
				left_border+=1;
				right_border-=1;
			}
		down_border+=fp->ornament_thickness;
		up_border-=fp->ornament_thickness;
		left_border+=fp->ornament_thickness;
		right_border-=fp->ornament_thickness;
	}
		break;
	case 2://pattern circle
	{
	int centerX = bmpf->dibh.width / 2;
    int centerY = bmpf->dibh.height / 2;
    int radius = (centerX < centerY) ? centerX : centerY;
	for (int i = 0; i < bmpf->dibh.height; i++) {
            for (int j = 0; j < bmpf->dibh.width; j++) {
                double distance = sqrt(pow((i - centerX),2) + pow((j - centerY),2));
                if (distance > radius) {
                	bmpf->rgb[i][j]=fp->ornament_color;
                }
            }
	}
		break;
	}
	case 3://pattern semicircle
	{
		int radiusX = ceil((double)(bmpf->dibh.height-fp->ornament_count*fp->ornament_thickness)/(2*fp->ornament_count));
        int radiusY = ceil((double)(bmpf->dibh.width-fp->ornament_count*fp->ornament_thickness)/(2*fp->ornament_count));
		
		int centerX = radiusX+fp->ornament_thickness;
		for (int i = 0; i < fp->ornament_count; i++){
            for (int x = centerX-radiusX-fp->ornament_thickness; x < centerX+radiusX+fp->ornament_thickness && x < bmpf->dibh.width && x >= 0; x++){
                /* down semicircles */
                for (int y = 0; y < radiusX+fp->ornament_thickness && y < bmpf->dibh.height && y >= 0; y++){
                    int centerY = 0;
                    double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
                    if ((distance < radiusX || distance > radiusX + fp->ornament_thickness)==0) {
                	bmpf->rgb[y][x]=fp->ornament_color;
					}
                }
				/* up semicircles */
                for (int y = bmpf->dibh.height-1; y > bmpf->dibh.height-1-radiusX-fp->ornament_thickness && y >= 0 && y < bmpf->dibh.height; y--){
                    int centerY = bmpf->dibh.height-1;
                    double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
                    if ((distance < radiusX || distance > radiusX + fp->ornament_thickness)==0){
                    	bmpf->rgb[y][x]=fp->ornament_color;
					}
                }
			}
			centerX += 2 * radiusX + fp->ornament_thickness;
		}

		int centerY=radiusY+fp->ornament_thickness;
		for (int i = 0; i < fp->ornament_count; i++){
            for (int y = centerY - radiusY - fp->ornament_thickness; y < centerY+radiusY+fp->ornament_thickness && y < bmpf->dibh.height && y >= 0; y++){
                /* Left semicircles */
                for (int x = 0; x < radiusY+fp->ornament_thickness && x < bmpf->dibh.width && x >= 0; x++){
                    int centerX = 0;
                    double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
                    if ((distance < radiusY || distance > radiusY + fp->ornament_thickness)==0) {
                    	bmpf->rgb[y][x]=fp->ornament_color;
                    }
                }
			
			 /* Right semicircles */
                for (int x = bmpf->dibh.width-1; x > bmpf->dibh.width-1-radiusY-fp->ornament_thickness && x < bmpf->dibh.width && x >= 0; x--){
                    int centerX = bmpf->dibh.width-1;
                    double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
                    if ((distance < radiusY || distance > radiusY + fp->ornament_thickness)==0) {
                    	bmpf->rgb[y][x]=fp->ornament_color;
                    }
                }
			}
			centerY += 2 * radiusX + fp->ornament_thickness;
		}
		break;
	}

	default:
		break;
	}

	return bmpf->rgb;
}

Rgb** rotate_image(FunctionParams* fp,BMPFile* bmpf){
		
		int size=bmpf->dibh.height*bmpf->dibh.width;
		Rgb** new_arr = malloc(size* sizeof(Rgb*));
		for (int i = 0; i < size; i++)
			new_arr[i] = malloc(bmpf->dibh.width* sizeof(Rgb));

		for (int i = 0; i < bmpf->dibh.height; i++){
			for (int j = 0; j < bmpf->dibh.width; j++){
				new_arr[i][j]=bmpf->rgb[i][j];
			}
		}
			
		switch (fp->rotate_angle)
		{
		case 90:
			for (int i = fp->rotate_down; i <= fp->rotate_up; i++)
				for (int j = fp->rotate_left; j <= fp->rotate_right; j++)
					bmpf->rgb[i][j]=new_arr[j][fp->rotate_up-i];
			break;
		case 180:
			for (int i = fp->rotate_down; i <= fp->rotate_up; i++)
				for (int j = fp->rotate_left; j <= fp->rotate_right; j++)
					bmpf->rgb[i][j]=new_arr[fp->rotate_up-i][fp->rotate_right-j];
			break;
		case 270:
			for (int i = fp->rotate_down; i <= fp->rotate_up; i++)
				for (int j = fp->rotate_left; j <= fp->rotate_right; j++)
					bmpf->rgb[i][j]=new_arr[fp->rotate_right-j][i]; 
			break;
		default:
			break;
		}
			
	for (int i = 0; i < bmpf->dibh.height; i++) 
    	free(new_arr[i]);
	free(new_arr);
	
	return bmpf->rgb;
}

#endif
