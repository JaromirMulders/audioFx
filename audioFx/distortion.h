#include "effect.h"
#include <math.h>
#include <complex.h>


class Distortion : public Effect
{
public:
  void process_samples(float *input, float *output, int frames, int *parameters);
  void settings();

  float timbre;
  float timbreInverse;
  float depth;

private:

}; // distortion
