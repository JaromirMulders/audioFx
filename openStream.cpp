Audio_IO audiostream;

void openStream()
{
  int input_device=0,output_device=0;

  audiostream.set_mode(AUDIO_IO_READWRITE);
  audiostream.set_samplerate(SAMPLERATE);
  audiostream.set_nrofchannels(NROFCHANNELS);
  audiostream.set_framesperbuffer(FRAMESPERBUFFER);

  audiostream.initialise();
  audiostream.list_devices();
  std::cout << "\nGive input device number: ";
  std::cin  >> input_device;
  audiostream.set_input_device(input_device);
  std::cout << "Give output device number: ";
  std::cin  >> output_device;
  audiostream.set_output_device(output_device);
  audiostream.start_server();

}
