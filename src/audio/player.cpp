#include "audio/player.h"

namespace loftili {

AudioPlayer::AudioPlayer() : playing(false), ready(true), audio_stream(0) {
  log = new Logger(this);
  log->info("new audio player created");

  mpg123_init();
  int success = Pa_Initialize();
  int devices = Pa_GetDeviceCount();

  if(success != paNoError || devices < 1)
    log->fatal("portaudio initialize fail");
  else 
    log->info("portaudio initialized and device ready to go");
}

AudioPlayer::~AudioPlayer() {
  delete log;

  if(audio_stream)
    delete audio_stream;

  Pa_Terminate();
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
  audio_stream = 0;

  playing = false;
}

}
