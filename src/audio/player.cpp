#include "audio/player.h"

namespace loftili {

AudioPlayer::AudioPlayer() : playing(false), ready(true), audio_stream(0) {
  log = new Logger(this);
  log->info("new audio player created");
}

AudioPlayer::~AudioPlayer() {
  delete log;

  if(audio_stream && playing)
    delete audio_stream;
}

bool AudioPlayer::finished() {
  if(!audio_stream)
    return false;

  bool is_finished = audio_stream->finished();
  return is_finished;
}

void AudioPlayer::start() {
  if((playing || !ready) && !finished())
    return;

  log->info("creating new audio stream");
  audio_stream = new AudioStream("/music/Fun/some_nights.mp3");
  playing = true;
  audio_stream->start();
}

void AudioPlayer::start(char* track_url) {
  if((playing || !ready) && !finished())
    return;

  log->info("creating new audio stream from url: ");
  log->info(track_url);

  audio_stream = new AudioStream(track_url);
  playing = true;
  audio_stream->start();
}

PlayerStatus AudioPlayer::status() {
  PlayerStatus status;
  status.playing = playing;
  status.position = playing ? audio_stream->position() : 0;
  status.duration = playing ? audio_stream->duration() : 0;
  status.downloading = playing ? audio_stream->downloading() : 0;
  return status;
}

void AudioPlayer::stop() {
  if(!playing)
    return;

  // audio_stream garbage collection
  log->info("cleaning up audio stream");
  delete audio_stream;
  audio_stream = NULL;
  playing = false;
}

}
