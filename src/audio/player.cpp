#include "audio/player.h"

namespace loftili {

AudioPlayer::AudioPlayer() : current_state(PLAYER_STATE_STOPPED), current_stream(0) {
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

  log->info("stopping the audio player");

  if(current_stream)
    delete current_stream;

  current_stream = 0;
  pthread_join(playback_thread, NULL);

  return current_state;
}

PLAYER_STATE AudioPlayer::start() {
  if(current_state == PLAYER_STATE_PLAYING)
    return current_state;

  log->info("starting the audio player");
  current_state = PLAYER_STATE_PLAYING;

  pthread_create(&playback_thread, NULL, AudioPlayer::monitor, (void*) this);
  return current_state;
}

void* AudioPlayer::monitor(void* player_instance_data) {
  AudioPlayer* current_player = (AudioPlayer*) player_instance_data;

  while(current_player->state() == PLAYER_STATE_PLAYING) {
    current_player->check();
    sleep(1);
  }

  return NULL;
}

int AudioPlayer::check() {
  log->info("running check against current audio stream");

  if(!current_stream) {
    log->info("not currently playing anything, loading in queue");
    QUEUE_STATUS queue_status = track_queue.load();

    if(queue_status != QUEUE_STATUS_FULL) {
      log->info("unable to load the track queue");
      current_state = PLAYER_STATE_ERRORED;
      return 0;
    }

    std::string track_url = track_queue.top();
    std::stringstream ss;

    ss << "queue ready, starting: " << track_url;
    current_stream = new AudioStream(track_url);
    current_stream->start();
  }

  return 0;
}

PLAYER_STATE AudioPlayer::state() {
  return current_state;
}

}
