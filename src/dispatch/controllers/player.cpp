#include "dispatch/controllers/player.h"

namespace loftili {

PlayerController::PlayerController() {
  name = "PlayerController";
  player = new AudioPlayer();
}

PlayerController::~PlayerController() {
  log->info("deleting the player controller");
  delete player;
}

int PlayerController::respondTo(Request* req, Response* res) {
  log->info("PlayerController is responding to: ");
  log->info(req->url);

  if(req->url == "/start")
    return start(req, res);
  else
    return stop(req, res);
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
