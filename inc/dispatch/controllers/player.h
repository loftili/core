#ifndef _LOFTILI_PLAYER_CONTROLLER_H
#define _LOFTILI_PLAYER_CONTROLLER_H

#include "dispatch/controller.h"
#include "audio/stream.h"

namespace loftili {

enum PLAYER_METHOD { 
  PLAYER_METHOD_START,
  PLAYER_METHOD_STOP,
  PLAYER_METHOD_STATUS
};

enum PLAYER_STATE {
  PLAYER_STATE_PLAYING,
  PLAYER_STATE_STOPPED,
  PLAYER_STATE_ERRORED
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
    AudioStream* current_stream;
    PLAYER_STATE current_state;

};

}


#endif
