#include "audio/player.h"

namespace loftili {

AudioPlayer::AudioPlayer() : playing(false) {
  std::cout << "creating the player" << std::endl;
}

AudioPlayer::~AudioPlayer() {
  std::cout << "closing the player" << std::endl;
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
