#ifndef _LOFTILI_PLAYER_CONTROLLER_H
#define _LOFTILI_PLAYER_CONTROLLER_H

#include "dispatch/controller.h"
#include "audio/player.h"

namespace loftili {

enum player_methods {
  START,
  STOP,
  STATUS
};

class PlayerController : public Controller {

  public:
    PlayerController();
    ~PlayerController();
    int respondTo(Request* req, Response* res);

  protected:
    std::string logName() { return "PlayerController"; }

  private:
    int start(Request* req, Response* res);
    int stop(Request* req, Response* res);
    int status(Request* req, Response* res);

  private:
    AudioPlayer* player;

};

}


#endif
