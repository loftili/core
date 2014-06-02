#ifndef _LOFTILI_PLAYER_CONTROLLER_H
#define _LOFTILI_PLAYER_CONTROLLER_H

#include "dispatch/controller.h"
#include "audio/player.h"
#include "audio/manager.h"

namespace loftili {

class PlayerController : public Controller {

public:
  PlayerController();
  ~PlayerController();
  Response* respondTo(Request* r);

protected:
  std::string logName() { return "PlayerController"; }

private:
  AudioPlayer* player;
  AudioManager* manager;

};

}


#endif
