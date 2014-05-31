#ifndef _LOFTILI_AUDIO_MANAGER_H
#define _LOFTILI_AUDIO_MANAGER_H

#include <iostream>
#include <pthread.h>
#include <ao/ao.h>

namespace loftili {

class Player;

class Manager {

  public:
    static void begin(Player* p);
    static void stop();

  private:
    static void* playbackFn(void* p);
    static void* loadFn(void* p);

    static pthread_t loading;
    static pthread_t playback;
    static Player* player;
    static int count;

};

}


#endif
