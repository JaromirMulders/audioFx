#include "distortion.h"


void Distortion::settings()
{
  //initial parameters
  timbre = 1;
  depth = 1;

}


//processing samples
void Distortion::process_samples(float *input, float *output, int frames, int *parameters)
{
  timbre = parameters[0];
  depth = parameters[1];

  timbre = (timbre / POTRESOLUTION) * 2.5 + 0.5;
  depth = (depth / POTRESOLUTION) * 2.5 + 0.5;

  timbreInverse = (1 - (timbre * 0.099)) * 10; //inverse scaling from timbre
  for(int bufptr=0; bufptr<frames; bufptr++) {

    input[bufptr] = input[bufptr] * depth;                               //volume scaling
    input[bufptr] = tanh((input[bufptr] * (timbre + 1)));                //smooth clipping
    input[bufptr] = (input[bufptr] * ((0.1 + timbre) * timbreInverse));  //scaling
    input[bufptr] = cos((input[bufptr] + (timbre + 0.25)));              //waveShapeing
    input[bufptr] = tanh(input[bufptr] * (timbre + 1));                  //Distorting
    input[bufptr] = input[bufptr] * 0.125;                               //volume scaling

    output[bufptr] = input[bufptr];                                      //write to output

  }

}
