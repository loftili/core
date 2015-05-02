#include "audio/player.h"

namespace loftili {

namespace audio {

Player::Player() : m_state(PLAYER_STATE_STOPPED) {
}

Player::Player(const Player& other) {
}

Player::~Player() {
}

Player& Player::operator=(const Player& other) {
  return *this;
}

Player::operator bool() {
  return m_state == PLAYER_STATE_PLAYING;
}

}

}
