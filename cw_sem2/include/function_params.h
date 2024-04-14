#include "bmp.h"

#ifndef FUNCTION_PARAMS_H
#define FUNCTION_PARAMS_H

FunctionParams* parse_command_line(int argc,char* argv[]);

FunctionParams* initFunctionalParams(FunctionParams* fp);

char** parse_line(char* line,int num_val);

void raise_error(const char* message, int error_code);

void check_rect(FunctionParams* fp,int height,int width);

void check_ornament(FunctionParams* fp);

void check_rotate(FunctionParams* fp,int height, int width);

#endif