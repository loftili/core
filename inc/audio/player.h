#ifndef _LOFTILI_AUDIO_PLAYER_H
#define _LOFTILI_AUDIO_PLAYER_H

namespace loftili {

namespace audio {

class Player {
  public:
    Player();
    Player(const Player&);
    Player& operator=(const Player&);
    operator bool();
    ~Player();
    enum PLAYER_STATE {
      PLAYER_STATE_ERRORED,
      PLAYER_STATE_PLAYING,
      PLAYER_STATE_STOPPED
    };
  private:
    PLAYER_STATE m_state;
};

}

}

#endif
