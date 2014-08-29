#include "dispatch/controllers/player.h"

namespace loftili {

PlayerController::PlayerController() {
  name = "PlayerController";
  player = new AudioPlayer();

  ControllerMethod start = ControllerMethod("/start", player_methods::START);
  ControllerMethod stop = ControllerMethod("/stop", player_methods::STOP);
  ControllerMethod status = ControllerMethod("/status", player_methods::STATUS);
  method_map.insert(start);
  method_map.insert(stop);
  method_map.insert(status);
}

PlayerController::~PlayerController() {
  log->info("deleting the player controller");
  delete player;
  delete log;
}

int PlayerController::respondTo(Request* req, Response* res) {
  log->info(std::string("PlayerController is responding to: ") + req->url);

  switch(req->c_method) {
    case START:
      return start(req, res);
    case STOP:
      return stop(req, res);
    case STATUS:
      return status(req, res);
  }
}

int PlayerController::status(Request* req, Response* res) {
  res->json("status", player->isPlaying() ? "playing" : "stopped");
}

int PlayerController::stop(Request* req, Response* res) {
  log->info("stoppping audio player");
  player->stop();
  return 0;
}

int PlayerController::start(Request* req, Response* res) {
  player->start();
  return 0;
}

}
