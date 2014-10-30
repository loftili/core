#include "dispatch/controllers/player.h"

namespace loftili {

PlayerController::PlayerController() : current_stream(0), current_state(PLAYER_STATE_STOPPED) {
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

  if(current_stream)
    delete current_stream;

  delete log;
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
  res->json(doc);
  delete doc;
  return 0;
}

int PlayerController::stop(Request* req, Response* res) {
  log->info("stoppping audio player");

  if(current_stream)
    delete current_stream;

  return 0;
}

int PlayerController::start(Request* req, Response* res) {
  char* track_url = req->query("track");
  if(track_url != NULL) {
    log->info("deleting previous audio stream");
    if(current_stream)
      delete current_stream;
    log->info("starting audio stream");
    current_stream = new AudioStream(track_url);
    current_stream->start();
  } else {
    missing(res);
  }
  return 0;
}

}
