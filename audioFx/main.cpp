#include "effect.h"
#include "emptyFx.h"
#include "delay.h"
#include "tremolo.h"
#include "distortion.h"
#include "filter.h"

#include <iostream>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <jack/jack.h>

#define FXAMOUNT 5

int frameAmount;

int effectNumber = 0;

int effectType;
int effectTypeArray[4] = {0,0,0,0};

//receiveControll---------------------------------------------------------------
int oldValue;

int potParams[3];
int potParams1[3];
int potParams2[3];
int potParams3[3];
int potParams4[3];

FILE *file;
unsigned char doorspoelChar;
const char *devicename="/dev/cu.usbmodem1421";


void receiveControll()
{
  do{
    fread(&doorspoelChar,1,1,file);
  } while (doorspoelChar < 128);

  potParams[0] = doorspoelChar & 127;
  fread(&doorspoelChar,1,1,file);

  potParams[1] = doorspoelChar & 127;
  fread(&doorspoelChar,1,1,file);

  potParams[2] = doorspoelChar & 127;
  fread(&doorspoelChar,1,1,file);

  effectNumber = doorspoelChar;
  fread(&doorspoelChar,1,1,file);

  effectType = doorspoelChar;
  fread(&doorspoelChar,1,1,file);

  effectTypeArray[effectNumber] = effectType;

  if(effectNumber == 0){
    potParams1[0] = potParams[0];
    potParams1[1] = potParams[1];
    potParams1[2] = potParams[2];
  } else
  if(effectNumber == 1){
    potParams2[0] = potParams[0];
    potParams2[1] = potParams[1];
    potParams2[2] = potParams[2];
  } else
  if(effectNumber == 2){
    potParams3[0] = potParams[0];
    potParams3[1] = potParams[1];
    potParams3[2] = potParams[2];
  } else
  if(effectNumber == 3){
    potParams4[0] = potParams[0];
    potParams4[1] = potParams[1];
    potParams4[2] = potParams[2];
  }


}


//bufferSwitch------------------------------------------------------------------
int bufIn = 0; //counters for switching buffer
int bufOut = 1;

void bufSwitch() //function for switching pointers to audio io buffers
{
  bufIn++;
  if (bufIn > 1){
    bufIn = 0;
  }

  bufOut = 1 - bufIn;
} //bufSwitch

//process-----------------------------------------------------------------------
//audi init
jack_port_t *input_port;
jack_port_t *output_port;

bool audioSetup = true;
float **bufferSwitch;   //switching buffer for audio io
Effect **effect;

int process(jack_nframes_t nframes, void *arg)
{
  //setup------------------------------------
  //initialising once within callback function
  if(audioSetup == true) {
    frameAmount = nframes;

    bufferSwitch = new float*[2];
    bufferSwitch[0] = new float[frameAmount];
    bufferSwitch[1] = new float[frameAmount];

    audioSetup = false;
  }//if

  //----------------------------------------------------------------------------

  jack_default_audio_sample_t *in =
    (jack_default_audio_sample_t *) jack_port_get_buffer(input_port, nframes);

  jack_default_audio_sample_t *out =
    (jack_default_audio_sample_t *) jack_port_get_buffer(output_port,nframes);

  for(int i = 0; i < nframes; i++){ //filling inputbuffer for switching buffer
    bufferSwitch[bufIn][i] = in[i];
  }//for

  effect[effectTypeArray[0]]->process_samples(bufferSwitch[bufIn],bufferSwitch[bufOut],nframes,potParams1);
  bufSwitch();
  effect[effectTypeArray[1]]->process_samples(bufferSwitch[bufIn],bufferSwitch[bufOut],nframes,potParams2);
  bufSwitch();
  effect[effectTypeArray[2]]->process_samples(bufferSwitch[bufIn],bufferSwitch[bufOut],nframes,potParams3);
  bufSwitch();
  effect[effectTypeArray[3]]->process_samples(bufferSwitch[bufIn],out,nframes,potParams4);



  return 0;
} // process()

//shutdown callback may be called by JACK---------------------------------------
void jack_shutdown(void *arg)
{
  exit(1);
}

//update Samplerate-------------------------------------------------------------
int updatesamplerate(jack_nframes_t nframes, void *arg)
{
  cout << "Sample rate set to: " << nframes << endl;
  return 0;
}

//main--------------------------------------------------------------------------
int main()
{
  //Settings--------------------------------------------------------------------
  //opening serial port from arduino
  file=fopen(devicename,"r");

  if(file==NULL){
    printf("Unable to open device %s\n",devicename);
    exit(1);
  }
  //creating fx pointers;
  effect = new Effect*[FXAMOUNT]; //size of array of effects
  effect[0] = new EmptyFx;
  effect[1] = new Delay;
  effect[2] = new Tremolo;
  effect[3] = new Distortion;
  effect[4] = new Filter;

  for(int i = 0; i<FXAMOUNT; i++){ //initialising all effects
    effect[i]->settings();
  }


  //starting up jack------------------------------------------------------------
  // Create a new Jack client

  jack_client_t *client;
  const char **ports;

  if( (client=jack_client_open("jackFx",(jack_options_t)0,0)) == 0)
  {
    cout << "JACK server not running ?\n";
    return 1;
  }

  // Install the sample processing callback
  jack_set_process_callback(client,process,0);

  // Install a shutdown routine
  jack_on_shutdown(client,jack_shutdown,0); // install a shutdown callback

  // Install a routine
  jack_set_sample_rate_callback(client,updatesamplerate,0);

  // Open an input port
  input_port = jack_port_register(client,"in",
     JACK_DEFAULT_AUDIO_TYPE,JackPortIsInput, 0);

  cout << "Our input port is called: " << jack_port_name(input_port) << endl;

  output_port = jack_port_register(client,"out",
     JACK_DEFAULT_AUDIO_TYPE,JackPortIsOutput,0);

  cout << "Our output port is called: " << jack_port_name(output_port) << endl;

  // Get rollin'
  if(jack_activate(client)){
    cout <<  "cannot activate client";
    return 1;
  }

  /*
   * The next calls try to auto-connect to a receiving client
   */
  // See what ports are available to receive our
  if((ports =
  jack_get_ports(client,"system|meter",0,JackPortIsInput)) == 0){
    cout << "Cannot find any physical playback ports\n";
    exit(1);
  }

  // List all ports matching the search criteria
  for(int p=0; ports[p] != 0; p++){
    cout << "Ports found: " << ports[p] << endl;
  }

  // first output
  if(jack_connect(client,jack_port_name(output_port),ports[0])){
    cout << "Cannot connect output ports\n";
  }

  // second output
  if(jack_connect(client,jack_port_name(output_port),ports[1])){
    cout << "Cannot connect output ports\n";
  }

  free(ports); // ports structure no longer needed


  while(1){

    receiveControll();
    //cout << potParams[0] << " " <<   potParams[1] << " "<<   potParams[2] << " " << effectNumber << " " << effectType << "\n";

  };

  jack_client_close(client);
  fclose(file);

  return 1;
}
