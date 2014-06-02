#ifndef _LOFTILI_PLAYER_H
#define _LOFTILI_PLAYER_H

#include <portaudio.h>
#include "util/logger.h"

namespace loftili {

class AudioPlayer : public Loggable {

public:
  AudioPlayer();
  ~AudioPlayer();
  void start();
  void stop();
  bool isPlaying();

protected:
  std::string logName() { return "AudioPlayer"; }

private:
  Logger* log;
  char* data;
  bool playing;

};

}


#endif
