#ifndef _LOFTILI_AUDIO_PLAYBACK_H
#define _LOFTILI_AUDIO_PLAYBACK_H

#include <iostream>

namespace loftili {

namespace audio {

class Playback {
  public:
    Playback();
    ~Playback();
    Playback(const Playback&);
    Playback& operator=(const Playback&);
    void Start();
    void Stop();
};

}

}


#endif
