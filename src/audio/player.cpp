#include "audio/player.h"

namespace loftili {

AudioPlayer::AudioPlayer() : current_state(PLAYER_STATE_STOPPED) {
  log = new Logger("Audio player");
}

AudioPlayer::~AudioPlayer() {
  delete log;
}

void AudioPlayer::initialize(Credentials device_credentials, Options device_options) {
  track_queue.initialize(device_credentials, device_options);
}

PLAYER_STATE AudioPlayer::stop() {
  current_state = PLAYER_STATE_STOPPED;
  return current_state;
}

PLAYER_STATE AudioPlayer::next() {
  return current_state;
}

PLAYER_STATE AudioPlayer::begin() {
  current_state = PLAYER_STATE_PLAYING;
  log->info("beginning audio player - finding queue from api");

  QUEUE_STATUS queue_status = track_queue.load();

  if(queue_status == QUEUE_STATUS_ERRORED) {
    current_state = PLAYER_STATE_ERRORED;
    return current_state;
  }

  return current_state;
}

PLAYER_STATE AudioPlayer::state() {
  return current_state;
}

}
