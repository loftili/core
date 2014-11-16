#ifndef _LOFTILI_PLAYER_CONTROLLER_H
#define _LOFTILI_PLAYER_CONTROLLER_H

#include "dispatch/controller.h"
#include "auth/credentials.h"
#include "util/options.h"
#include "audio/player.h"

namespace loftili {

enum PLAYER_METHOD { 
  PLAYER_METHOD_START,
  PLAYER_METHOD_STOP,
  PLAYER_METHOD_REFRESH,
  PLAYER_METHOD_STATUS
};

class PlayerController : public Controller {

  public:
    PlayerController();
    ~PlayerController();
    int respondTo(Request* req, Response* res);
    void initialize(Credentials init_credentials, Options init_options);

  protected:
    std::string logName() { return "PlayerController"; }

  private:
    int start(Request* req, Response* res);
    int stop(Request* req, Response* res);
    int status(Request* req, Response* res);
    int refresh(Request* req, Response* res);

  private:
    AudioPlayer player;

};

}


#endif
