#include "emptyFx.h"

void EmptyFx::settings()
{

}

void EmptyFx::process_samples(float *input, float *output, float *parameters){

  for(int bufptr=0; bufptr<buffersize; bufptr++) {

    output[bufptr] = input[bufptr];

  }//for

}//process_samples
