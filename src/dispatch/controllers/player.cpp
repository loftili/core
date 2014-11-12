#include "dispatch/controllers/player.h"

namespace loftili {

PlayerController::PlayerController() {
  name = "PlayerController";
  ControllerMethod start = ControllerMethod("/start", PLAYER_METHOD_START);
  ControllerMethod stop = ControllerMethod("/stop", PLAYER_METHOD_STOP);
  ControllerMethod status = ControllerMethod("/status", PLAYER_METHOD_STATUS);
  method_map.insert(start);
  method_map.insert(stop);
  method_map.insert(status);
}

PlayerController::~PlayerController() {
  log->info("deleting the player controller");
  delete log;
}

void PlayerController::initialize(Credentials init_credentials, Options init_options) {
  log = new Logger("PlayerController");
  device_options = init_options;
  device_credentials = init_credentials;
  log->info("initalizing player controller");
  player.initialize(device_credentials, device_options);
}

int PlayerController::respondTo(Request* req, Response* res) {
  log->info(std::string("PlayerController is responding to: ") + req->url);

  switch(req->c_method) {
    case PLAYER_METHOD_START:
      return start(req, res);
    case PLAYER_METHOD_STOP:
      return stop(req, res);
    case PLAYER_METHOD_STATUS:
      return status(req, res);
  }
}

int PlayerController::status(Request* req, Response* res) {
  Json* doc = new Json();

  PLAYER_STATE player_state = player.state();

  switch(player_state) {
    case PLAYER_STATE_PLAYING:
      doc->insert("status", "playing");
      break;
    case PLAYER_STATE_STOPPED:
      doc->insert("status", "stopped");
      break;
    case PLAYER_STATE_ERRORED:
      doc->insert("status", "errored");
      break;
    default:
      doc->insert("status", "unknown");
      break;
  }

  res->json(doc);
  delete doc;
  return 0;
}

int PlayerController::stop(Request* req, Response* res) {
  log->info("stoppping audio");
  player.stop();
  return status(req, res);
}

int PlayerController::start(Request* req, Response* res) {
  PLAYER_STATE state = player.state();

  if(state == PLAYER_STATE_PLAYING)
    return 0;

  log->info("telling audio player to start");

  player.begin();

  return status(req, res);
}

}
