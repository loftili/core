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

QUEUE_STATUS TrackQueue::load() {
  log->info("fetching track queue");
  Request request;
  Response response("", 0);

  request.url = endpoint();
  request.method = "GET";
  request.addHeader("x-loftili-device-auth", device_credentials.token());
  request.send(&response);

  rapidjson::Document queue_document;
  queue_document.Parse<0>((char*)response.content);
  std::cout << (char*)response.content << std::endl;

  bool can_use = queue_document.IsArray();

  if(!can_use)
    return QUEUE_STATUS_ERRORED;

  int size = queue_document.Size();
  for(int i = 0; i < size; i++) {
    rapidjson::Value& queue_item = queue_document[i];

    bool has_url = queue_item["streaming_url"].IsString();
    if(has_url) {
      std::string track_url = (std::string) queue_document[i]["streaming_url"].GetString();
      track_urls.push_back(track_url);
    }
  }

  return QUEUE_STATUS_FULL;
}

}
