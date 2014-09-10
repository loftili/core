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

void AudioPlayer::start() {
  if(playing || !ready)
    return;

  log->info("creating new audio stream");
  audio_stream = new AudioStream("/music/Fun/some_nights.mp3");
  audio_stream->start();
  playing = true;
}

bool AudioPlayer::isPlaying() {
  return playing;
}

void AudioPlayer::stop() {
  if(!playing)
    return;

  // audio_stream garbage collection
  log->info("cleaning up audio stream");
  delete audio_stream;
  playing = false;
}

}
