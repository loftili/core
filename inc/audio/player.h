#ifndef _LOFTILI_AUDIO_PLAYER_H
#define _LOFTILI_AUDIO_PLAYER_H

#include "loftili.h"
#include "auth/credentials.h"
#include "audio/stream.h"
#include "util/options.h"
#include "audio/track_queue.h"

namespace loftili {

enum PLAYER_STATE {
  PLAYER_STATE_PLAYING,
  PLAYER_STATE_STOPPED,
  PLAYER_STATE_ERRORED
};

class AudioPlayer {

  public:
    AudioPlayer();
    ~AudioPlayer();
    PLAYER_STATE state();
    PLAYER_STATE begin();
    PLAYER_STATE stop();
    PLAYER_STATE next();
    void initialize(Credentials device_credentials, Options device_options);

  private:
    Logger* log;
    PLAYER_STATE current_state;
    TrackQueue track_queue;
    AudioStream* current_stream;

};

}

#endif
