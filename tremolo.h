#include "effect.h"
#include <math.h>

class Tremolo : public Effect
{
public:
  //functions
  void process_samples(float *input, float *output, float *parameters);
  void settings();

  //variables
  int waveform;
  int polState;

  float speed;
  float depth;

private:
  unsigned long x;

}; // Tremelo
