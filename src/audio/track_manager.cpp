#include "audio/track_manager.h"

namespace loftili {

TrackManager::TrackManager() : device_options(), device_credentials() {
  log = new Logger("TrackManager");
}

TrackManager::~TrackManager() {
  delete log;
}

std::string TrackManager::endpoint() {
  std::stringstream ss;
  int device_id = device_credentials.deviceId();
  ss << (device_options.api_host != "" ? device_options.api_host : LOFTILI_API_HOME);
  ss << "/queues/" << device_id << "/pop";
  return ss.str();
}

void TrackManager::initialize(Credentials init_creds, Options init_opts) {
  device_credentials = init_creds;
  device_options = init_opts;
}

std::string TrackManager::pop() {
  string first_track = track_urls.front();
  track_urls.pop();
  return first_track;
}

QUEUE_STATUS TrackManager::status() {
  return QUEUE_STATUS_EMPTY;
}

QUEUE_STATUS TrackManager::fetch() {
  log->info("fetching track queue");
  Request* request = new Request();
  Response* response = new Response("", 0);

  stringstream pop_url;
  pop_url << endpoint() << "?device_token=" << device_credentials.token();

  request->url = pop_url.str();
  request->method = "POST";
  request->send(response);

  if(response->status == 204) {
    log->info("track queue was empty!");
    delete request;
    delete response;
    return QUEUE_STATUS_EMPTY;
  }

  if(response->status != 200) {
    log->info("track queue fetch returned non 200 status code, failing");
    log->info((char*) response->content);
    delete response;
    delete request;
    return QUEUE_STATUS_ERRORED;
  }

  rapidjson::Document popped_track_info;
  popped_track_info.Parse<0>((char*) response->content);

  bool can_use = popped_track_info.IsObject();

  if(!can_use) {
    delete response;
    delete request;
    return QUEUE_STATUS_ERRORED;
  }

  can_use = popped_track_info["streaming_url"].IsString();

  if(!can_use) {
    delete response;
    delete request;
    return QUEUE_STATUS_ERRORED;
  }

  string track_url = (string) popped_track_info["streaming_url"].GetString();
  track_urls.push(track_url);

  delete response;
  delete request;

  return QUEUE_STATUS_FULL;
}

}
