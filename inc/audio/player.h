#ifndef _LOFTILI_AUDIO_PLAYER_H
#define _LOFTILI_AUDIO_PLAYER_H

#include <iostream>
#include <memory>
#include <unistd.h>
#include <fstream>
#include <mpg123.h>
#include <ao/ao.h>
#include "config.h"
#include "spdlog/spdlog.h"
#include "net/url.h"
#include "net/http_client.h"
#include "net/http_request.h"

namespace loftili {

namespace audio {

class Player {
  public:
    Player() = default;
    Player(const Player&) = default;
    Player& operator=(const Player&) = default;
    ~Player() = default;

    bool Play(std::string);
    int State() { return m_state; };
    void Stop();
    operator bool();

    enum PLAYER_STATE {
      PLAYER_STATE_ERRORED,
      PLAYER_STATE_PLAYING,
      PLAYER_STATE_STOPPED
    };

  private:
    void Startup();
    void Shutdown();
    PLAYER_STATE m_state;
    std::unique_ptr<std::string> m_stream;
};

}

}

#endif
