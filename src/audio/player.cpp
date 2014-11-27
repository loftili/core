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
  current_state = next();

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

PLAYER_STATE AudioPlayer::next() {
  if(current_stream)
    delete current_stream;

  QUEUE_STATUS queue_status = track_queue.fetch();

  if(queue_status != QUEUE_STATUS_FULL) {
    log->info("unable to load the track queue");
    current_state = PLAYER_STATE_ERRORED;
    switch(queue_status) {
      case QUEUE_STATUS_ERRORED:
        last_error = "unable to load track queue information";
        break;
      case QUEUE_STATUS_EMPTY:
        last_error = "empty track queue";
        break;
      default:
        last_error = "unknown error occurred";
        break;
    }
    return current_state;
  }

  current_track_url = track_queue.pop();
  std::stringstream queue_log;
  queue_log << "queue ready, starting: " << current_track_url;
  log->info(queue_log.str());
  current_stream = new AudioStream(current_track_url);
  current_stream->start();

  current_state = PLAYER_STATE_PLAYING;
  return current_state;
}

string AudioPlayer::trackURL() {
  return current_track_url;
}

int AudioPlayer::check() {
  log->info("running check against current audio stream");
  STREAM_STATE current_stream_state = current_stream->state();

  switch(current_stream_state) {
    case STREAM_STATE_BUFFERING:
      log->info("still buffering audio, proceeding");
      break;
    case STREAM_STATE_PLAYING:
      log->info("still playing audio stream");
      break;
    case STREAM_STATE_ERRORED:
      log->info("errored playing stream, invalidating player status");
      current_state = PLAYER_STATE_ERRORED;
      break;
    case STREAM_STATE_FINISHED:
      log->info("finished playing latest track since last refresh, moving to next");
      current_state = next();
      break;
    default:
      log->info("unkown state, agh!");
      break;
  }

  return 0;
}

string AudioPlayer::lastError() {
  return last_error;
}

STREAM_STATE AudioPlayer::streamState() {
  return current_stream ? current_stream->state() : STREAM_STATE_EMPTY;
}

PLAYER_STATE AudioPlayer::state() {
  return current_state;
}

}
