#include "services/playback_manager.h"

namespace loftili {

PlaybackManager::PlaybackManager() {
  log = new Logger("PlaybackManager");
  player = new AudioPlayer();
  relay = new StateRelay();
  last_player_state = PLAYER_STATE_STOPPED;
  canceled = false;
}

PlaybackManager::~PlaybackManager() {
  log->info("destroying playback manager");
  canceled = true;

  if(player)
    delete player;

  player = 0;

  if(monitor_thread)
    pthread_join(monitor_thread, NULL);

  delete log;
  delete relay;
}

PLAYER_STATE PlaybackManager::start() {
  PLAYER_STATE received = player->start();

  if(received == PLAYER_STATE_PLAYING || received == PLAYER_STATE_BUFFERING) {
    canceled = false;
    log->info("playback manager opening up monitor thread!");
    pthread_create(&monitor_thread, NULL, PlaybackManager::monitor, (void*) this);
  }

  return received;
}

void* PlaybackManager::monitor(void* playback_instance) {
  PlaybackManager* manager = (PlaybackManager*) playback_instance;
  Logger* log = new Logger("::PlaybackManager");
  StateRelay* relay = new StateRelay();

  PLAYER_STATE manager_state = manager->state();
  relay->send("player:state", manager_state);

  while(true) {
    if(manager->canceled)
      break;

    PLAYER_STATE new_state = manager->state();

    if(new_state != manager_state) {
      log->info("detected state change, sending to api");
      relay->send("player:state", new_state);

      bool is_stopped = new_state == PLAYER_STATE_STOPPED;
      bool was_playing = manager_state == PLAYER_STATE_PLAYING;

      if(is_stopped && was_playing)
        manager->next();
    }

    manager_state = new_state;

    usleep(100000);
  }
  
  delete relay;
  delete log;

  return NULL;
}

PLAYER_STATE PlaybackManager::state() {
  return player->state();
}

PLAYER_STATE PlaybackManager::next() {
  return player->next();
}

PLAYER_STATE PlaybackManager::stop() {
  canceled = true;

  if(monitor_thread)
    pthread_join(monitor_thread, NULL);

  PLAYER_STATE pstate = player->stop();

  monitor_thread = NULL;

  relay->send("player:state", pstate);
  last_player_state = pstate;

  return pstate;
}

}
