#ifndef _LOFTILI_AUDIO_QUEUE_H
#define _LOFTILI_AUDIO_QUEUE_H

#include <iostream>
#include <queue> 
#include "config.h"
#include "spdlog/spdlog.h"
#include "api.h"
#include "rapidjson/document.h"
#include "api/registration.h"
#include "audio/player.h"
#include "net/http_client.h"
#include "net/http_request.h"

namespace loftili {

namespace audio {

class Queue {
  public:
    friend class Parser;
    Queue() = default;
    Queue(const Queue&) = default;
    Queue& operator=(const Queue&) = default;
    ~Queue() = default;

    bool operator>>(loftili::audio::Player&);
    void Pop();

  private:
    const std::string QueueUrl();
    std::queue<std::string> m_queue;
};

}

}

#endif
