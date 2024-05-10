#include "errors.h"

#ifndef ERRORS_C
#define ERRORS_C


const char* color_error="Error: Invalid color format";

const char* coords_error="Error: Invalid coordinates";

const char* thickness_error="Error: Invalid thickness";

const char* pattern_error="Error: Invalid pattern";

const char* count_error="Error: Invalid count";

const char* angle_error="Error: Invalid angle";


const char* args_error="Error: Invalid arguments";

const char* multiple_func_error="Error: More than one functions were called";

const char* input_file_error="Error: No input file";

const char* output_file_error="Error: No output file";

const char* file_type_error="Error: Incorrect file type";

const char* file_opening_error="Error: Can't open file";

void raiseError(const char* message, int error_code){
    printf("%s\n",message);
    exit(error_code);
}

#endif