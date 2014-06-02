#include "audio/player.h"

namespace loftili {

AudioPlayer::AudioPlayer() : playing(false) {
  log = new Logger(this);
  int success = Pa_Initialize();

  if(success != paNoError)
    log->fatal("Unable to load portaudio library");
  else
    log->info("Successfully loaded portaudio library");
}

AudioPlayer::~AudioPlayer() {
  Pa_Terminate();
  delete log;
}

void AudioPlayer::start() {
  playing = true;
}

bool AudioPlayer::isPlaying() {
  return playing;
}

void AudioPlayer::stop() {
  playing = false;
}

}
