#include "audio/track_manager.h"

namespace loftili {

TrackManager::TrackManager() {
  log = new Logger("TrackManager");
}

TrackManager::~TrackManager() {
  delete log;
}

std::string TrackManager::endpoint() {
  std::stringstream ss;
  int device_id = loftili::config->device_id;
  ss << (loftili::config->api_host != "" ? loftili::config->api_host : LOFTILI_API_HOME);
  ss << "/queues/" << device_id << "/pop";
  return ss.str();
}

Track TrackManager::pop() {
  Track first_track = track_list.front();

  stringstream log_msg;
  log_msg << "popping track[" << first_track.track_url << "]";
  log->info(log_msg.str());

  track_list.pop();
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
  pop_url << endpoint() << "?device_token=" << loftili::config->token;
  log->info("sending pop request to ", pop_url.str());

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

  Track fetched_track;
  fetched_track.track_url = (string) popped_track_info["streaming_url"].GetString();
  fetched_track.track_id = (int) popped_track_info["id"].GetInt();

  track_list.push(fetched_track);

  delete response;
  delete request;

  return QUEUE_STATUS_FULL;
}

}
