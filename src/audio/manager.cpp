#include <audio/manager.h>
#include <audio/player.h>

namespace loftili {

pthread_t Manager::loading;
pthread_t Manager::playback;
int Manager::count;
Player* Manager::player;

void* Manager::playbackFn(void* p) {
}

void* Manager::loadFn(void* p) {
  while(player->isPlaying()) {
    std::cout << count << std::endl;
    count ++;
  }
}

void Manager::begin(Player* p) {
  if(player != NULL) {
    std::cout << "already started!" << std::endl;
    return;
  }
  
  count = 0;
  player = p;

  std::cout << "starting manager" << std::endl;

  pthread_create(&loading, NULL, &loadFn, p);
  pthread_create(&playback, NULL, &playbackFn, p);
}

void Manager::stop() {
  std::cout << "stopping manager" << std::endl;

  void* ret;
  pthread_join(loading, &ret);
  
  pthread_join(playback, &ret);
  std::cout << "completely finished!" << std::endl;

  player = NULL;
}

}
