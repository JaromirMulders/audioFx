#include "effect.h"

class EmptyFx : public Effect
{
public:
  //functions
  void process_samples(float *input, float *output, float *parameters);
  void settings();

private:

}; // Tremelo
