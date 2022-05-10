#include "emptyFx.h"

void EmptyFx::settings()
{

}

void EmptyFx::process_samples(float *input, float *output, int frames, int *parameters){

  for(int bufptr=0; bufptr<frames; bufptr++) {

    output[bufptr] = input[bufptr];

  }//for

}//process_samples
