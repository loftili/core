#include "dispatch/controllers/player.h"

namespace loftili {

PlayerController::PlayerController() {
  name = "PlayerController";

  ControllerMethod start = ControllerMethod("/start", PLAYER_METHOD_START);
  ControllerMethod stop = ControllerMethod("/stop", PLAYER_METHOD_STOP);
  ControllerMethod status = ControllerMethod("/status", PLAYER_METHOD_STATUS);
  ControllerMethod refresh = ControllerMethod("/restart", PLAYER_METHOD_REFRESH);
  ControllerMethod next = ControllerMethod("/next", PLAYER_METHOD_NEXT);

  method_map.insert(start);
  method_map.insert(stop);
  method_map.insert(status);
  method_map.insert(refresh);
  method_map.insert(next);

  playback = new PlaybackManager();
}

PlayerController::~PlayerController() {
  log->info("deleting the player controller");
  delete log;
  delete playback;
}

void PlayerController::initialize(Credentials init_credentials, Options init_options) {
  log = new Logger("PlayerController");
  device_options = init_options;
  device_credentials = init_credentials;
  log->info("initalizing player controller");
  playback->initialize(device_credentials, device_options);
}

int PlayerController::respondTo(Request* req, Response* res) {
  log->info(std::string("PlayerController is responding to: ") + req->url);

  switch(req->c_method) {
    case PLAYER_METHOD_START:
      return start(req, res);
    case PLAYER_METHOD_STOP:
      return stop(req, res);
    case PLAYER_METHOD_REFRESH:
      return refresh(req, res);
    case PLAYER_METHOD_NEXT:
      return next(req, res);
    case PLAYER_METHOD_STATUS:
      return status(req, res);
    default:
      return 0;
  }
}

int PlayerController::status(Request* req, Response* res) {
  Json* doc = new Json();

  PLAYER_STATE player_state = playback->state();

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
    case PLAYER_STATE_BUFFERING:
      doc->insert("status", "buffering");
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
  playback->stop();
  return status(req, res);
}

int PlayerController::start(Request* req, Response* res) {
  PLAYER_STATE state = playback->state();

  if(state == PLAYER_STATE_PLAYING)
    return status(req, res);

  log->info("telling audio player to start");
  playback->start();

  return status(req, res);
}

int PlayerController::refresh(Request* req, Response* res) {
  log->info("stopping player");
  playback->stop();
  log->info("starting player");
  playback->start();
  return status(req, res);
}

int PlayerController::next(Request* req, Response* res) {
  log->info("telling player to skip to next track");
  return refresh(req, res);
}

}
