#include "dispatch/controllers/player.h"

namespace loftili {

PlayerController::~PlayerController() {
  log->info("deleting the player controller");
  delete player;
}

void PlayerController::initialize() {
  name = "PlayerController";
  player = new AudioPlayer();
}

Response* PlayerController::respondTo(Request* request) {
  Response* r = new Response(200);
  log->info("PlayerController is responding to: ");
  log->info(request->url);

  if(request->url == "/start")
    player->start();
  else
    player->stop();

  return r;
}

}
