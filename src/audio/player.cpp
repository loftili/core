#include "audio/player.h"

namespace loftili {

namespace audio {

Player::Player() : m_state(PLAYER_STATE_STOPPED) {
}

Player::Player(const Player& other) {
}

Player::~Player() {
}

bool Player::Play(std::string url) {
  std::cout << "playing: " << url << std::endl;
  return false;
}

Player& Player::operator=(const Player& other) {
  return *this;
}

Player::operator bool() {
  return m_state == PLAYER_STATE_PLAYING;
}

}

}
