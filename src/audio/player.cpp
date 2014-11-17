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
    QUEUE_STATUS queue_status = track_queue.fetch();

    if(queue_status != QUEUE_STATUS_FULL) {
      log->info("unable to load the track queue");
      current_state = PLAYER_STATE_ERRORED;
      return 0;
    }

    std::string track_url = track_queue.top();
    std::stringstream queue_log;
    queue_log << "queue ready, starting: " << track_url;
    log->info(queue_log.str());
    current_stream = new AudioStream(track_url);
    current_stream->start();
    return 0;
  }

  log->info("already playing audio, checking state");
  STREAM_STATE current_stream_state = current_stream->state();

  switch(current_stream_state) {
    case STREAM_STATE_BUFFERING:
    case STREAM_STATE_PLAYING:
      log->info("still playing or buffering audio, proceeding");
      break;
    case STREAM_STATE_ERRORED:
      log->info("errored playing stream, invalidating player status");
      current_state = PLAYER_STATE_ERRORED;
      break;
    case STREAM_STATE_FINISHED:
      log->info("finished playing latest track since last refresh, moving to next");
      break;
    default:
      log->info("unkown state, agh!");
      break;
  }

  return 0;
}

PLAYER_STATE AudioPlayer::state() {
  return current_state;
}

}
