#ifndef _LOFTILI_PLAYER_CONTROLLER_H
#define _LOFTILI_PLAYER_CONTROLLER_H

#include "dispatch/controller.h"
#include "audio/player.h"

namespace loftili {

class PlayerController : public Controller {

public:
  ~PlayerController();
  void initialize();
  Response* respondTo(Request* r);

private:
  Player* player;

};

}


#endif
