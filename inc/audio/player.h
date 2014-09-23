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

struct PlayerStatus {
  bool playing;
  int position;
  int duration;
  bool downloading;
};

class AudioPlayer : public Loggable {

  public:
    AudioPlayer();
    ~AudioPlayer();
    void start();
    void start(char* track_url);
    void stop();
    PlayerStatus status();
    off_t position();

  protected:
    std::string logName() { return "AudioPlayer"; }

  private:
    bool prepare();
    bool finished();

  private:
    Logger* log;
    bool playing;
    bool ready;
    AudioStream* audio_stream;

};

}

#endif
