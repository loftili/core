#ifndef _LOFTILI_PLAYBACK_MANAGER_H
#define _LOFTILI_PLAYBACK_MANAGER_H

#include "loftili.h"
#include "util/logger.h"
#include "audio/player.h"
#include "services/state_relay.h"

namespace loftili {

class PlaybackManager {

  public:
    PlaybackManager();
    ~PlaybackManager();

    PLAYER_STATE start();
    PLAYER_STATE stop();
    PLAYER_STATE state();
    PLAYER_STATE next();

  protected:
    bool canceled;

  private:
    static void* monitor(void* player_instance_data);

    StateRelay* relay;
    AudioPlayer* player;
    Logger* log;
    pthread_t monitor_thread;
    PLAYER_STATE last_player_state;

};

}

#endif
