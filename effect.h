#pragma once
#include <iostream>

#define SAMPLERATE		44100
#define NROFCHANNELS	1
#define FRAMESPERBUFFER		64


class Effect
{
public:
  Effect();
  virtual void process_samples(float *input, float *output, float *parameters);
  virtual void settings();

protected:
  float buffersize;

}; // Effect
