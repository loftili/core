#ifndef _LOFTILI_PLAYBACK_MANAGER_H
#define _LOFTILI_PLAYBACK_MANAGER_H

#include "loftili.h"
#include "audio/player.h"
#include "util/logger.h"

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
    PLAYER_STATE checkLoop();
    bool canceled;

  private:
    static void* monitor(void* player_instance_data);

    AudioPlayer* player;
    Logger* log;
    pthread_t monitor_thread;
    PLAYER_STATE last_player_state;

};

}

#endif
