#ifndef _LOFTILI_AUDIO_QUEUE_H
#define _LOFTILI_AUDIO_QUEUE_H

#include <iostream>
#include <queue> 
#include "api.h"
#include "rapidjson/document.h"
#include "api/registration.h"
#include "audio/player.h"
#include "net/request.h"
#include "net/response_stream.h"
#include "net/response.h"

namespace loftili {

namespace audio {

class Queue {
  public:
    friend class Parser;
    Queue(const loftili::api::DeviceCredentials&);
    Queue(const Queue&);
    Queue& operator=(const Queue&);
    bool operator>>(loftili::audio::Player&);
    void Pop();
    ~Queue();
  private:
    std::queue<std::string> m_queue;
    loftili::api::DeviceCredentials m_credentials;
};

}

}

#endif
