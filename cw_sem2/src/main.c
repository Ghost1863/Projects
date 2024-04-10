#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmp.h"
#include "processing.h"
#include "function_params.h"

int main(char argc, char* argv[]){
   
   FunctionParams* fp=parse_command_line(argc,argv);
   BMPFile* bmpf=read_bmp(fp->input_file);
    
   //print_file_header(bmpf->bmph);
   //print_info_header(bmpf->dibh);
   if (fp->rect)
      bmpf->rgb=draw_rectangle(fp,bmpf);
   if (fp->ornament)
      bmpf->rgb=draw_ornament(fp,bmpf);
   if (fp->rotate)
      bmpf->rgb=rotate_image(fp,bmpf);
   

   write_bmp(fp->output_file,bmpf);

   free_bmpfile(bmpf);
   free(fp);
   return 0;
}