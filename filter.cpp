#include "filter.h"
//24db lowpass filter by: Timo Tossavainen
//source:: http://musicdsp.org/showArchiveComment.php?ArchiveID=26

void Filter::settings()
{
  //parameters
  frequency = 0.1;
  resonance = 0.1;

  in1 = 0;
  in2 = 0;
  in3 = 0;
  in4 = 0;
  out1 = 0;
  out2 = 0;
  out3 = 0;
  out4 = 0;

}

void Filter::process_samples(float *input, float *output, float *parameters)
{

  frequency = parameters[0];
  resonance = parameters[1];

  frequency = frequency / 120;
  resonance = resonance / 100;

  for(int bufptr=0; bufptr<FRAMESPERBUFFER; bufptr++) {

    if(frequency < 0.05){
      frequency = 0.05;
    }
    if(frequency > 0.95){
      frequency = 0.95;
    }

    //filter
    f = frequency * 1.16;
    fb = resonance * (1 - 0.15 * f * f);
    input[bufptr] = input[bufptr] - out4 * fb;
    input[bufptr] = input[bufptr] * (f*f) * (f*f);

    out1 = input[bufptr] + 0.3 * in1 + (1 - f) * out1; // Pole 1
    in1 = input[bufptr];//sample delay
    out2 = out1 + 0.3 * in2 + (1 - f) * out2; // Pole 2
    in2 = out1;         //sample delay
    out3 = out2 + 0.3 * in3 + (1 - f) * out3; // Pole 3
    in3 = out2;         //sample delay
    out4 = out3 + 0.3 * in4 + (1 - f) * out4; // Pole 4
    in4 = out3;         //sample delay

    output[bufptr] = out4;
  }//for

}//filter
