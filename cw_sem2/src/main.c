#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmp.h"
#include "processing.h"
#include "function_params.h"

int main(char argc, char* argv[]){
   
   FunctionParams* fp=parseCommandLine(argc,argv);
   BMPFile* bmpf=readBMP(fp->input_file);
   
   if (fp->rect){
      checkRect(fp,bmpf->dibh.height,bmpf->dibh.width);
      bmpf->rgb=drawRectangle(fp,bmpf);
   }
   if (fp->ornament){
      checkOrnament(fp);
      bmpf->rgb=drawOrnament(fp,bmpf);
   }
   if (fp->rotate){
      checkRotate(fp,bmpf->dibh.height,bmpf->dibh.width);
      bmpf->rgb=rotateImage(fp,bmpf);
   }
   
   writeBMP(fp->output_file,bmpf);
   
   freeBMPfile(bmpf);
   free(fp);
   return 0;
}