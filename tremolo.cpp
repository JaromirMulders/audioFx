#include "tremolo.h"

//------------------------------------------------------
void Tremolo::settings()
{
  waveform = 1;
  speed = 0.5;
  depth = 1;
}

//------------------------------------------------------
//waveshaping clipping for triangle
float triangle(float inlet){
  if(inlet < 0){
    inlet = 0;
  }

  return inlet;
}

//------------------------------------------------------
//waveshaping clipping for square
float square(float inlet)
{
  if(inlet > 0.5){
    inlet = 1;
  } else {
    inlet = 0;
  }
  return inlet;
}

void Tremolo::process_samples(float *input, float *output, float *parameters){

  waveform = parameters[0];
  speed = parameters[1];
  depth = parameters[2];

  waveform = waveform / 33 + 1;
  speed = speed / 2;
  depth = depth / 100;

  for(int bufptr=0; bufptr<buffersize; bufptr++) {
    //------------------------------------------------------
    //sine
    if (waveform == 1){
      input[bufptr] = (input[bufptr] * (depth * (sin((double) x * speed/SAMPLERATE * M_PI * 2.))));

    } else
    //------------------------------------------------------
    //triangle
    if (waveform == 2){
      input[bufptr] =
      (input[bufptr] * (depth * (triangle(fmod((x * speed/SAMPLERATE),1) * 2 - 1) +           //ranmp up of a sawtooth with clipping from 0 to 1
                                triangle((fmod((x * speed/SAMPLERATE),1) * 2 - 1) * -1))));  //inversion of ramp up with clipping from 0 to 1

    } else
    //------------------------------------------------------
    //square
    if (waveform == 3){
      input[bufptr] =
        (input[bufptr] * square((depth * fmod((x * speed/SAMPLERATE),1))));

    } else
    //------------------------------------------------------
    //saw
    if (waveform == 4){
      input[bufptr] =
        (input[bufptr] * (depth * fmod((x * speed/SAMPLERATE),1)));

    }

    output[bufptr] = input[bufptr];
    x++; //counter for modulation oscillators
  }//for

}//process_samples
