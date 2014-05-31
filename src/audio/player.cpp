#include "audio/player.h"

namespace loftili {

Player::Player() : playing(false) {
  std::cout << "creating the player" << std::endl;
}

Player::~Player() {
  std::cout << "closing the player" << std::endl;
}

void Player::start() {
  playing = true;
  Manager::begin(this);
}

bool Player::isPlaying() {
  return playing;
}

void Player::stop() {
  playing = false;
  Manager::stop();
}

}
