#include "delay.h"


void Delay::settings()
{

  tapin = 0;  //read head
  tapout = 0; //write head
  //initial state effect
  delayTime = 22000;
  feedback = 0.5;

}

void Delay::process_samples(float *input, float *output, int frames, int *parameters)
{

  delayTime = parameters[0];
  feedback = parameters[1];

  delayTime = delayTime * POTRESOLUTION + 100;
  feedback = feedback / POTRESOLUTION;

  for(int bufptr=0; bufptr<frames; bufptr++) {
    if(tapin >= DELAYBUFFERSIZE){
      tapin = 0;

    }

    tapout = tapin - delayTime;

    if(tapout < 0){
      tapout = tapout + DELAYBUFFERSIZE;

    }

    delayBuffer[tapin] = input[bufptr] + (delayBuffer[tapout] * feedback);
    output[bufptr] = delayBuffer[tapin];

    tapin++;
  }

}//delay
