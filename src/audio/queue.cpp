#include "audio/queue.h"

namespace loftili {

namespace audio {

Queue::Queue() {
};

Queue::~Queue() {
};

Queue::Queue(const Queue& other) {
};

Queue& Queue::operator=(const Queue& other) {
  return *this;
};

bool Queue::operator>>(loftili::audio::Player& player) {
  std::string host = "127.0.0.1";
  std::string method = "GET";
  std::string path = "/system";
  int port = 1337;
  loftili::net::Request r(method, host, port, path);
  int s = r.Send();
  printf("loading queue into player\n");
  return false;
}

}

}
