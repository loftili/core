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
  player->stop();

  ShallowJson json;
  json["status"] = "started";

  res->json(&json);
  return 0;
}

int PlayerController::start(Request* req, Response* res) {
  player->start();
  res->json();
  return 0;
}

}
