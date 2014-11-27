#ifndef _LOFTILI_AUDIO_PLAYER_H
#define _LOFTILI_AUDIO_PLAYER_H

#include "loftili.h"
#include "auth/credentials.h"
#include "audio/stream.h"
#include "util/options.h"
#include "audio/track_manager.h"

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
    string lastError();
    PLAYER_STATE state();
    PLAYER_STATE start();
    PLAYER_STATE stop();
    PLAYER_STATE next();
    string trackURL();
    void initialize(Credentials device_credentials, Options device_options);

  protected:
    pthread_t playback_thread;

  private:
    int check();
    static void* monitor(void* player_instance_data);

    string last_error;
    string current_track_url;
    Logger* log;
    PLAYER_STATE current_state;
    TrackManager track_queue;
    AudioStream* current_stream;

};

}

#endif
