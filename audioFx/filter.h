#include "effect.h"
#include <math.h>


class Filter : public Effect
{
public:
  void process_samples(float *input, float *output, int frames, int *parameters);
  void settings();

  float frequency;
  float resonance;

  float f;
  float fb;

  float in1;
  float in2;
  float in3;
  float in4;
  float out1;
  float out2;
  float out3;
  float out4;

private:

}; // filter
