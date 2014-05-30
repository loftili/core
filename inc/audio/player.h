#ifndef _LOFTILI_PLAYER_H
#define _LOFTILI_PLAYER_H

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ao/ao.h>

namespace loftili {

class Player {

public:
  Player();
  ~Player();
  void start();
  void stop();

private:
  ao_device* device;
  int ao_driver;
  ao_sample_format format;
  char *buffer;
  int buf_size;
  int sample;
  float freq;

};

}


#endif
