#ifndef _LOFTILI_AUDIO_QUEUE_H
#define _LOFTILI_AUDIO_QUEUE_H

#include <iostream>
#include <queue> 
#include "audio/player.h"
#include "net/request.h"

namespace loftili {

namespace audio {

class Queue {
  public:
    Queue();
    Queue(const Queue&);
    Queue& operator=(const Queue&);
    bool operator>>(loftili::audio::Player&);
    ~Queue();
  private:
    std::queue<std::string> m_queue;
};

}

}

#endif
