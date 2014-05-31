#ifndef _LOFTILI_PLAYER_H
#define _LOFTILI_PLAYER_H

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <audio/manager.h>

namespace loftili {

class Player {

public:
  Player();
  ~Player();
  void start();
  void stop();
  bool isPlaying();

private:
  char* data;
  bool playing;

};

}


#endif
