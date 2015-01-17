#ifndef _LOFTILI_AUDIO_PLAYER_H
#define _LOFTILI_AUDIO_PLAYER_H

#include "loftili.h"
#include "audio/stream.h"
#include "audio/track_manager.h"

namespace loftili {

class AudioPlayer {

  public:
    AudioPlayer();
    ~AudioPlayer();

    PLAYER_STATE state();
    PLAYER_STATE start();
    PLAYER_STATE stop();
    PLAYER_STATE next();

  private:
    PLAYER_ERROR last_error;
    Logger* log;
    Track current_track_info;
    TrackManager track_queue;
    AudioStream* current_stream;

};

}

#endif
