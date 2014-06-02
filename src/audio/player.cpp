#include "audio/player.h"

namespace loftili {

AudioPlayer::AudioPlayer() : playing(false) {
  std::cout << "creating the player" << std::endl;
  int success = Pa_Initialize();
  if(success != paNoError)
    std::cout << "had trouble initializing portaudio" << std::endl;
  else
    std::cout << "initialized portaudio" << std::endl;
}

AudioPlayer::~AudioPlayer() {
  std::cout << "closing the player" << std::endl;
  Pa_Terminate();
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
