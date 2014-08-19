#include "audio/player.h"

namespace loftili {

AudioPlayer::AudioPlayer() : playing(false), ready(true), audio_stream(0) {
  log = new Logger(this);
  log->info("new audio player created");

  mpg123_init();
  int success = Pa_Initialize();
  int devices = Pa_GetDeviceCount();

  if(success != paNoError || devices < 1) {
    std::cout << "-!> portaudio initialize fail" << std::endl;
  }

  std::cout << "-> portaudio initialized and ready" << std::endl;
}

AudioPlayer::~AudioPlayer() {
  delete log;
  delete audio_stream;
  Pa_Terminate();
}

void AudioPlayer::start() {
  if(playing || !ready)
    return;

  log->info("Creating new audio stream");
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

  if(audio_stream != 0) {
    audio_stream->stop();
    audio_stream->clean();
  }

  playing = false;
}

}
