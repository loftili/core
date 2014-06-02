#include "dispatch/controllers/player.h"

namespace loftili {

PlayerController::~PlayerController() {
  std::cout << "deleting the player controller" << std::endl;
  delete player;
}

void PlayerController::initialize() {
  name = "PlayerController";
  player = new AudioPlayer();
}

Response* PlayerController::respondTo(Request* request) {
  Response* r = new Response(200);
  std::cout << "PlayerController is responding to: " << request->url << std::endl;

  if(request->url == "/start")
    player->start();
  else
    player->stop();

  return r;
}

}
