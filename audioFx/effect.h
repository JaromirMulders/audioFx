#pragma once
#include <iostream>

#define SAMPLERATE 44100
#define POTRESOLUTION 127

class Effect
{
public:
  Effect();
  virtual void process_samples(float *input, float *output, int frames, int *parameters);
  virtual void settings();

protected:
  float buffersize;

}; // Effect
