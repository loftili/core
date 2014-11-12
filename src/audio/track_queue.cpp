#include "audio/track_queue.h"

namespace loftili {

TrackQueue::TrackQueue() : device_options(), device_credentials() {
  log = new Logger("TrackQueue");
}

TrackQueue::~TrackQueue() {
  delete log;
}

std::string TrackQueue::endpoint() {
  std::stringstream ss;
  int device_id = device_credentials.deviceId();
  ss << (device_options.api_host != "" ? device_options.api_host : LOFTILI_API_HOME);
  ss << "/queues/" << device_id;
  return ss.str();
}

void TrackQueue::initialize(Credentials init_creds, Options init_opts) {
  device_credentials = init_creds;
  device_options = init_opts;
}

void TrackQueue::load() {
  log->info("fetching track queue");
  log->info(device_credentials.token());
  Request request;
  Response response("", 0);

  request.url = endpoint();
  request.method = "GET";
  request.addHeader("x-loftili-device-auth", device_credentials.token());
  request.send(&response);

  std::cout << endpoint() << std::endl;
  std::cout << (char*) response.content << std::endl;
}

}
