#include "bmp.h"

#ifndef FUNCTION_PARAMS_H
#define FUNCTION_PARAMS_H

FunctionParams* parseCommandLine(int argc,char* argv[]);

FunctionParams* initFunctionalParams(FunctionParams* fp);

char** parseLine(char* line,int num_val);

void checkRect(FunctionParams* fp,int height,int width);

void checkOrnament(FunctionParams* fp);

void checkRotate(FunctionParams* fp,int height, int width);

void checkFunctionsNumber(FunctionParams* fp);

#endif