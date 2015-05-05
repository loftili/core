#include "audio/player.h"

namespace loftili {

namespace audio {

bool Player::Play(std::string url) {
  std::cout << "playing: " << url << std::endl;
  sleep(5);
  return true;
}

Player::operator bool() {
  return m_state == PLAYER_STATE_PLAYING;
}

}

}
