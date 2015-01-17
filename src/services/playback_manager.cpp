#include "services/playback_manager.h"

namespace loftili {

PlaybackManager::PlaybackManager() {
  log = new Logger("PlaybackManager");
  player = new AudioPlayer();
  last_player_state = PLAYER_STATE_STOPPED;
  canceled = false;
}

PlaybackManager::~PlaybackManager() {
  canceled = true;

  if(player)
    delete player;

  player = 0;

  if(monitor_thread)
    pthread_join(monitor_thread, NULL);

  delete log;
}

void PlaybackManager::initialize(Credentials device_credentials, Options device_options) {
  player->initialize(device_credentials, device_options);
}

PLAYER_STATE PlaybackManager::start() {
  PLAYER_STATE received = player->start();

  if(received == PLAYER_STATE_PLAYING || received == PLAYER_STATE_BUFFERING)
    pthread_create(&monitor_thread, NULL, PlaybackManager::monitor, (void*) this);

  return received;
}

void* PlaybackManager::monitor(void* playback_instance) {
  PlaybackManager* manager = (PlaybackManager*) playback_instance;

  PLAYER_STATE manager_state;

  while(true) {
    if(manager->canceled)
      return NULL;

    manager_state = manager->checkLoop();

    bool is_buffering = manager_state == PLAYER_STATE_BUFFERING;
    bool is_playing = manager_state == PLAYER_STATE_PLAYING;

    if(!is_buffering && !is_playing)
      return NULL;

    usleep(100000);
  }
  
  return NULL;
}

PLAYER_STATE PlaybackManager::checkLoop() {
  PLAYER_STATE current_state = player->state();

  if(current_state == last_player_state)
    return last_player_state;

  stringstream ss;
  ss << "detected state change, new state[" << current_state << "] last state[" << last_player_state << "]";
  log->info(ss.str());

  bool was_playing = last_player_state == PLAYER_STATE_PLAYING;
  bool is_stopped = current_state == PLAYER_STATE_STOPPED;

  last_player_state = current_state;

  if(was_playing && is_stopped) {
    log->info("was playing, now stopped, moving on");
    return player->next();
  }

  return current_state;
}

PLAYER_STATE PlaybackManager::state() {
  return player->state();
}

PLAYER_STATE PlaybackManager::next() {
  return player->next();
}

PLAYER_STATE PlaybackManager::stop() {
  PLAYER_STATE pstate = player->stop();

  if(monitor_thread)
    pthread_join(monitor_thread, NULL);

  monitor_thread = NULL;

  return pstate;
}

}
