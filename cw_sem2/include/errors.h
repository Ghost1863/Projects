#include <stdlib.h>
#include <stdio.h>

#ifndef ERRORS_H
#define ERRORS_H

#define ERR_FILE_NOT_FOUND 40

#define ERR_INCORRECT_FILE_FORMAT 41

#define ERR_FILE_WRITE_ERROR 42

#define ERR_INVALID_ARGUMENT 43

#define ERR_INSUFFICIENT_ARGUMENTS 45

#define ERR_MEMORY_ALLOCATION_FAILURE 46


extern const char* color_error;

extern const char* coords_error;

extern const char* thickness_error;

extern const char* pattern_error;

extern const char* count_error;

extern const char* angle_error;


extern const char* args_error;

extern const char* multiple_func_error;

extern const char* input_file_error;

extern const char* output_file_error;

extern const char* file_type_error;

extern const char* file_opening_error;


void raiseError(const char* message, int error_code);


#endif