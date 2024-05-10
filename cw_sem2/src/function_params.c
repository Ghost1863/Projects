#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "function_params.h"
#include "structures.h"
#include "errors.h"

#ifndef FUNCTION_PARAMS_C
#define FUNCTION_PARAMS_C

char** parseLine(char* line,int num_val){
    char** parsed_line=malloc(20*sizeof(char*));
    for (int i=0;i<num_val;i++){
        parsed_line[i]=malloc(strlen(line)*sizeof(char));
    }
    int current=0;
    int len=0 ;
    for (int i = 0; i < strlen(line); i++){
            if(i>0 && line[i-1]=='.'){
                parsed_line[current][len-1]='\0';        
                current++;
                len=0;
            }
            parsed_line[current][len++]=line[i];
        }
    parsed_line[current][len]='\0';
    return parsed_line;    
}

FunctionParams* initFunctionalParams(FunctionParams* fp){
    fp->rect=false;
    fp->fill=false;
    fp->x0=0;
	fp->x1=0;
	fp->y0=0;
	fp->y1=0;
	fp->thickness=0;
	fp->color.r=-1;fp->color.g=-1;fp->color.b=-1;
    fp->fill_color.r=-1;fp->fill_color.g=-1;fp->fill_color.b=-1;

    fp->ornament=false;
	fp->pattern=0;
	fp->count=0;

	fp->rotate=false;
	fp->angle=0;

    fp->help=true;
    fp->input_file=NULL;
    fp->output_file=NULL;
}

FunctionParams* parseCommandLine(int argc,char* argv[]){
    
    opterr=0;
    const char* short_options = "hi:o:";
    const struct option long_options[] = {
            {"help", 0, NULL, 'h'},
            {"input", 1, NULL, 'i'},
            {"output", 1, NULL, 'o'},
            {"rect", 0, NULL, 256},
            {"left_up", 1, NULL, 257},
            {"right_down", 1, NULL, 258},
            {"thickness", 1, NULL, 259},
            {"color", 1, NULL, 260},
            {"fill", 0, NULL, 261},
            {"fill_color", 1, NULL, 262},
            {"ornament", 0, NULL, 263},
            {"pattern", 1, NULL, 264},
            {"count", 1, NULL, 265},
            {"rotate", 0, NULL, 266},
            {"angle", 1, NULL, 267},
            {NULL, 0, NULL, 0}
     };
  
    FunctionParams* fp=malloc(sizeof(FunctionParams));
    initFunctionalParams(fp);

    int result=0;
    while ((result = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
        switch (result)
        {
        case 'h'://-help
            printHelp();
            break;

        case 'i'://-input
            fp->input_file=optarg;
            break;

        case 'o'://-output
            fp->output_file=optarg;
            break;

        case 256://--rect
            fp->rect=true;   
            break;

        case 257://--left_up
            fp->x0 = strtol(parseLine(optarg,2)[0], NULL, 10);
            fp->y0= strtol(parseLine(optarg,2)[1], NULL, 10);
            break;

        case 258://--right_down
            fp->x1 = strtol(parseLine(optarg,2)[0], NULL, 10);
            fp->y1= strtol(parseLine(optarg,2)[1], NULL, 10);
            break;

        case 259://--thickness
            fp->thickness=strtol(optarg,NULL,10);
            break;

        case 260://--color
            fp->color.r=strtol(parseLine(optarg,3)[0], NULL, 10);
            fp->color.g=strtol(parseLine(optarg,3)[1], NULL, 10);
            fp->color.b=strtol(parseLine(optarg,3)[2], NULL, 10);
            break;

        case 261://--fill
            fp->fill=true;
            break;
            
        case 262://--fill_color
            fp->fill_color.r=strtol(parseLine(optarg,3)[0], NULL, 10);
            fp->fill_color.g=strtol(parseLine(optarg,3)[1], NULL, 10);
            fp->fill_color.b=strtol(parseLine(optarg,3)[2], NULL, 10);
            break;

        case 263://--ornament
            fp->ornament=true;
            break;

        case 264://--pattern
            if(strcmp(optarg,"rectangle")==0){
                fp->pattern=1;
            }
            else if(strcmp(optarg,"circle")==0){
                fp->pattern=2;
            }
            else if(strcmp(optarg,"semicircles")==0){
                fp->pattern=3;
            }
            break;

        case 265://--count
            fp->count=strtol(optarg,NULL,10);;
            break;

        case 266://--rotate
            fp->rotate=true;
            break;

        case 267://--angle
            fp->angle=strtol(optarg,NULL,10);
            break;
            
        case '?':
            raiseError(args_error,43);
            break;
            
        default:
            
            break;
        }
     }
    
    checkFunctionsNumber(fp);
    if(!fp->input_file)
        exit(0);
    if(!fp->output_file)
        exit(0);
    return fp;
}

void swap(int* a,int* b){
    int temp= *a;
    *a=*b;
    *b=temp;
}

void checkFunctionsNumber(FunctionParams* fp){
    int count=0;
    if(fp->rect) 
        count++;
    if(fp->ornament)
        count++;
    if(fp->rotate)
        count++;
    if (count>1)
        raiseError(multiple_func_error,43);
}

void checkRect(FunctionParams* fp,int height, int width){
    if(fp->thickness<=0)
        raiseError(thickness_error,43);   
    if (fp->color.r>255 || fp->color.g>255 ||fp->color.b>255 ||
    fp->color.r<0 || fp->color.g<0 ||fp->color.b<0)
        raiseError(color_error,43);
    if(fp->fill){
        if (fp->fill_color.r>255 || fp->fill_color.g>255 ||fp->fill_color.b>255||
        fp->fill_color.r<0 || fp->fill_color.g<0 ||fp->fill_color.b<0)
            raiseError(color_error,43);
    }
}

void checkOrnament(FunctionParams* fp){
    if (fp->pattern==0)
        raiseError(pattern_error,43);
    if(fp->thickness<=0)
        raiseError(thickness_error,43); 
    if(fp->count<=0)
        raiseError(count_error,43);
    if (fp->color.r>255 || fp->color.g>255 || fp->color.b>255||
    fp->color.r<0 || fp->color.g<0 || fp->color.b<0)
        raiseError(color_error,43);  
}

void checkRotate(FunctionParams* fp,int height,int width){
    if(fp->x0<0)
        fp->x0=0;

    if(fp->x1<0)
        fp->x1=0;

    if(fp->y0<0)
        fp->y0=0;

    if(fp->y1<0)
        fp->y1=0;

     if(fp->x0>=width)
        fp->x0=width-1;

    if(fp->x1>=width)
        fp->x1=width-1;

    if(fp->y0>=height)
        fp->y0=height-1;
        
    if(fp->y1>=height)
        fp->y1=height-1;
    
    if (fp->angle!=90 && fp->angle!=180 && fp->angle!=270)
       raiseError(angle_error,43);
}
#endif