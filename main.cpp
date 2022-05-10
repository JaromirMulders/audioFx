#include "audio_io.h"
#include "distortion.h"
#include "tremolo.h"
#include "delay.h"
#include "filter.h"
#include "emptyFx.h"
#include "openStream.cpp"
#include "osc_server.h"

#include <iostream>
#include <cstdlib>


int bufIn = 0; //counters for switching buffer
int bufOut = 1;

localOSC osc;

//parameters for all effects
float parameters [5] = {0,0,0,0,0};
float parameters1[5] = {0,0,0,0,0};
float parameters2[5] = {0,0,0,0,0};
float parameters3[5] = {0,0,0,0,0};
float parameters4[5] = {0,0,0,0,0};

int param1 = 1;
int param2 = 1;
int param3 = 1;
int param4 = 1;
int param5 = 1;

int type1 = 1;
int type2 = 1;
int type3 = 1;
int type4 = 1;

int fxSel = 0;

//------------------------------------------------------
void bufSwitch() //function for switching pointers to audio io buffers
{
  bufIn++;
  if (bufIn > 1){
    bufIn = 0;
  }

  bufOut = 1 - bufIn;
} //bufSwitch

//------------------------------------------------------
void getOsc()
{
  osc.set_callback("/effectType","iiii");
  osc.getTypes(type1,type2,type3,type4);

  osc.set_callback("/effectSelect","i");
  osc.getSelect(fxSel);

  osc.set_callback("/params","iiiii");
  osc.getParams(param1,param2,param3,param4,param5);

  parameters[0] = param1;
  parameters[1] = param2;
  parameters[2] = param3;
  parameters[3] = param4;
  parameters[4] = param5;

  //filling parameter arrays with values if selected
  if(fxSel == 0){
    for (int i=0;i <= 4; i++){ //initializing effects
    parameters1[i] = parameters[i];
    }
  }else if(fxSel == 1){
    for (int i=0;i <= 4; i++){ //initializing effects
    parameters2[i] = parameters[i];
    }
  }else if(fxSel == 2){
    for (int i=0;i <= 4; i++){ //initializing effects
    parameters3[i] = parameters[i];
    }
  }else if(fxSel == 3){
    for (int i=0;i <= 4; i++){ //initializing effects
    parameters4[i] = parameters[i];
    }//else if
  }

}

//------------------------------------------------------
int main()
{
  int x = 0;
  int y = 0;

  string serverport="7777";
  osc.init(serverport);
  osc.start();
  std::cout << "Listening on port " << serverport << endl;

  float **bufferSwitch;   //switching buffer for audio io
  bufferSwitch = new float*[2];
  bufferSwitch[0] = new float[FRAMESPERBUFFER * NROFCHANNELS];
  bufferSwitch[1] = new float[FRAMESPERBUFFER * NROFCHANNELS];

  Effect **effect;
  effect = new Effect*[5]; //size of array of effects
  effect[0] = new EmptyFx;
  effect[1] = new Distortion;
  effect[2] = new Tremolo;
  effect[3] = new Delay;
  effect[4] = new Filter;

  openStream(); //open io settings and starting audio

  for (int i=0;i <= 4; i++){ //initializing effects
    effect[i]->settings();
  }//for

  while(true) //running audio trough effects
  {
    audiostream.read(bufferSwitch[bufIn]);

    y = x % 64; //check osc parameters every 64 samples
    if(y > 62){
      getOsc(); //getting parameters
    }
    x++;

    effect[type1]->process_samples(bufferSwitch[bufIn],bufferSwitch[bufOut],parameters1); //

    bufSwitch(); //switching buffers
    effect[type2]->process_samples(bufferSwitch[bufIn],bufferSwitch[bufOut],parameters2);

    bufSwitch();
    effect[type3]->process_samples(bufferSwitch[bufIn],bufferSwitch[bufOut],parameters3);

    bufSwitch();
    effect[type4]->process_samples(bufferSwitch[bufIn],bufferSwitch[bufOut],parameters4);

    audiostream.write(bufferSwitch[bufOut]);
  } //while

//------------------------------------------------------
  audiostream.finalise();
  return 0;

} // main()
