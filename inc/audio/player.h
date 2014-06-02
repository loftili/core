#ifndef _LOFTILI_PLAYER_H
#define _LOFTILI_PLAYER_H

#include <iostream>
#include <portaudio.h>

namespace loftili {

class AudioPlayer {

public:
  AudioPlayer();
  ~AudioPlayer();
  void start();
  void stop();
  bool isPlaying();

private:
  char* data;
  bool playing;

};

}


#endif
