#ifndef _LOFTILI_AUDIO_PLAYER_H
#define _LOFTILI_AUDIO_PLAYER_H

#include <iostream>
#include <memory>
#include <unistd.h>

namespace loftili {

namespace audio {

class Player {
  public:
    Player() = default;
    Player(const Player&) = default;
    Player& operator=(const Player&) = default;
    ~Player() = default;

    bool Play(std::string);
    operator bool();

    enum PLAYER_STATE {
      PLAYER_STATE_ERRORED,
      PLAYER_STATE_PLAYING,
      PLAYER_STATE_STOPPED
    };

  private:
    PLAYER_STATE m_state;
    std::unique_ptr<std::string> m_stream;
};

}

}

#endif
