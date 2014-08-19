#ifndef _LOFTILI_PLAYER_H
#define _LOFTILI_PLAYER_H

#include <string>
#include <iostream>
#include <sstream>
#include <portaudio.h>
#include <mpg123.h>

#include "util/logger.h"
#include "audio/stream.h"

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
  bool prepare();

private:
  Logger* log;
  bool playing;
  bool ready;
  AudioStream* audio_stream;

};

}

#endif
