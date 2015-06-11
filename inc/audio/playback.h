#ifndef _LOFTILI_AUDIO_PLAYBACK_H
#define _LOFTILI_AUDIO_PLAYBACK_H

#include <iostream>
#include <unistd.h>
#include <thread>
#include <mpg123.h>
#include "config.h"
#include "spdlog/spdlog.h"
#include "api/registration.h"
#include "api/state_client.h"
#include "audio/queue.h"
#include "audio/player.h"

namespace loftili {

class Engine;

namespace audio {

class Playback {
  public:
    Playback() = default;
    ~Playback() = default;
    Playback(const Playback&) = default;
    Playback& operator=(const Playback&) = default;

    void Skip();
    void Start();
    void Stop();

    enum PLAYBACK_STATE {
      PLAYBACK_STATE_STOPPED,
      PLAYBACK_STATE_ERRORED,
      PLAYBACK_STATE_PLAYING
    };

  private:
    void Run();
    std::thread m_thread;
    loftili::audio::Queue m_queue;
    loftili::audio::Player m_player;
    loftili::api::StateClient m_stateclient;
    PLAYBACK_STATE m_state;
    std::mutex m_mutex;

};

}

}


#endif
