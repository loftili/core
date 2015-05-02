#ifndef _LOFTILI_AUDIO_PLAYBACK_H
#define _LOFTILI_AUDIO_PLAYBACK_H

#include <iostream>
#include <unistd.h>
#include <thread>
#include "audio/queue.h"
#include "audio/player.h"

namespace loftili {

class Engine;

namespace audio {

class Playback {
  public:
    Playback();
    ~Playback();
    Playback(const Playback&);
    Playback& operator=(const Playback&);
    void Start();
    void Stop();

    enum PLAYBACK_STATE {
      PLAYBACK_STATE_PLAYING, 
      PLAYBACK_STATE_STOPPED,
      PLAYBACK_STATE_ERRORED
    };

  private:
    void Run();
    std::thread *m_thread;
    loftili::audio::Queue m_queue;
    loftili::audio::Player m_player;
    PLAYBACK_STATE m_state;

};

}

}


#endif
