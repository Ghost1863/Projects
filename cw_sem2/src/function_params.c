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

char** parse_line(char* line,int num_val){
    char** parsed_line=malloc(20*sizeof(char*));
    for (int i=0;i<num_val;i++){
        parsed_line[i]=malloc(strlen(line)*sizeof(char));
    }
    int current=0;
    int len=0;
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
    fp->rect_fill=false;
    fp->rect_left=-1000;
	fp->rect_up=-1000;
	fp->rect_right=-1000;
	fp->rect_down=-1000;
	fp->rect_thickness=-1;
	fp->rect_color.r=0;fp->rect_color.g=0;fp->rect_color.b=0;
    fp->rect_fill_color.r=0;fp->rect_fill_color.g=0;fp->rect_fill_color.b=0;

    fp->rotate=false;
    fp->ornament=false;
    fp->input_file=NULL;
    fp->output_file=NULL;
}

void raise_error(const char* message, int error_code){
    printf("%s\n",message);
    exit(error_code);
}

FunctionParams* parse_command_line(int argc,char* argv[]){
    
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
            printf("1");
            break;
        case 'i'://-input
            fp->input_file=optarg;
            break;
        case 'o'://-output
            fp->output_file=optarg;
            break;
        case 256://--rect
            if(!fp->ornament && !fp->rotate)
                fp->rect=true;
            else
                raise_error(multiple_func_error,43);          
            break;
        case 257://--left_up
            if (fp->rect){
                fp->rect_left = strtol(parse_line(optarg,2)[0], NULL, 10);
                fp->rect_up= strtol(parse_line(optarg,2)[1], NULL, 10);
            }else if (fp->rotate){
                fp->rotate_left = strtol(parse_line(optarg,2)[0], NULL, 10);
                fp->rotate_up= strtol(parse_line(optarg,2)[1], NULL, 10);
            }
            break;
        case 258://--right_down
            if (fp->rect){
                fp->rect_right = strtol(parse_line(optarg,2)[0], NULL, 10);
                fp->rect_down= strtol(parse_line(optarg,2)[1], NULL, 10);
            } else if(fp->rotate){
                fp->rotate_right = strtol(parse_line(optarg,2)[0], NULL, 10);
                fp->rotate_down= strtol(parse_line(optarg,2)[1], NULL, 10);
            }
            break;
        case 259://--thickness
            if (fp->rect)
                fp->rect_thickness=strtol(optarg,NULL,10);
            else if(fp->ornament)
                fp->ornament_thickness=strtol(optarg,NULL,10);
            break;
        case 260://--color
            if (fp->rect){
                fp->rect_color.r=strtol(parse_line(optarg,3)[0], NULL, 10);
                fp->rect_color.g=strtol(parse_line(optarg,3)[1], NULL, 10);
                fp->rect_color.b=strtol(parse_line(optarg,3)[2], NULL, 10);
            }else if(fp->ornament){
                fp->ornament_color.r=strtol(parse_line(optarg,3)[0], NULL, 10);
                fp->ornament_color.g=strtol(parse_line(optarg,3)[1], NULL, 10);
                fp->ornament_color.b=strtol(parse_line(optarg,3)[2], NULL, 10);
            }
            break;
        case 261://--fill
            fp->rect_fill=true;
            break;
        case 262://--fill_color
            fp->rect_fill_color.r=strtol(parse_line(optarg,3)[0], NULL, 10);
            fp->rect_fill_color.g=strtol(parse_line(optarg,3)[1], NULL, 10);
            fp->rect_fill_color.b=strtol(parse_line(optarg,3)[2], NULL, 10);
            break;
        case 263://--ornament
            if(!fp->rect && !fp->rotate)
                fp->ornament=true;
            else
                raise_error(multiple_func_error,43);  
            break;
        case 264://--pattern
            if(strcmp(optarg,"rectangle")==0){
                fp->ornament_pattern=1;
            }
            else if(strcmp(optarg,"circle")==0){
                fp->ornament_pattern=2;
            }
            else if(strcmp(optarg,"semicircle")==0){
                fp->ornament_pattern=3;
            }
            break;
        case 265://--count
            fp->ornament_count=strtol(optarg,NULL,10);;
            break;
        case 266://--rotate
            if(!fp->ornament && !fp->rect)
                fp->ornament=true;
            else
                raise_error(multiple_func_error,43);  
            break;
        case 267://--angle
            fp->rotate_angle=strtol(optarg,NULL,10);
            break;

        default:
            break;
        }
     }
    
    if(!fp->input_file)
        raise_error(input_file_error,40);
    if(!fp->output_file)
        raise_error(output_file_error,40);
    if (fp->rect)
      check_rect(fp);
    if (fp->ornament)
      check_ornament(fp);
    if (fp->rotate)
      check_rotate(fp);
      
    return fp;
}

void check_rect(FunctionParams* fp){
    if(fp->rect_left>fp->rect_right || fp->rect_up<fp->rect_down||
    fp->rect_left<0 || fp->rect_right<0 || fp->rect_up<0 || fp->rect_down<0) 
        raise_error(coords_error,45);
    if(fp->rect_thickness<=0)
        raise_error(thickness_error,45);   
}

void check_ornament(FunctionParams* fp){
      if(fp->ornament_thickness<=0)
        raise_error(thickness_error,45);   
}

void check_rotate(FunctionParams* fp){
    if(fp->rotate_left>fp->rotate_right || fp->rotate_up<fp->rotate_down||
    fp->rect_left<0 || fp->rotate_right<0 || fp->rotate_up<0 || fp->rotate_down<0) 
        raise_error(coords_error,45);
}
#endif