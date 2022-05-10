#include "effect.h"

#define DELAYBUFFERSIZE 44100

class Delay : public Effect
{
public:
  //functions
  void process_samples(float *input, float *output, int frames, int *parameters);
  void settings();

  float delayBuffer[DELAYBUFFERSIZE];
  int delayTime;
  int tapin;
  int tapout;
  float feedback;

private:

}; // Delay
