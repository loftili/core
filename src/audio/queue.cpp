#include "audio/queue.h"

namespace loftili {

namespace audio {

void Queue::Pop() {
  loftili::net::HttpClient client;
  std::string popurl = QueueUrl();
  popurl.append("/pop");
  loftili::net::HttpRequest req(loftili::net::Url(popurl.c_str()), "POST");
  req.Header(LOFTILI_API_TOKEN_HEADER, loftili::api::credentials.token);
  req.Header(LOFTILI_API_SERIAL_HEADER, loftili::api::configuration.serial);
  client.Send(req);
  return;
};

bool Queue::operator>>(loftili::audio::Player& player) {
  loftili::net::HttpClient client;
  loftili::net::HttpRequest req(loftili::net::Url(QueueUrl().c_str()));
  req.Header(LOFTILI_API_TOKEN_HEADER, loftili::api::credentials.token);
  req.Header(LOFTILI_API_SERIAL_HEADER, loftili::api::configuration.serial);
  spdlog::get(LOFTILI_SPDLOG_ID)->info("retreiving track queue from {0}", QueueUrl().c_str());

  if(client.Send(req)) {
    std::shared_ptr<loftili::net::HttpResponse> res = client.Latest();

    if(res->Status() != 200) {
      spdlog::get(LOFTILI_SPDLOG_ID)->warn("queue request received bad status code from api");
      return false;
    }

    rapidjson::Document document;
    document.Parse(res->Body());
    const rapidjson::Value& a = document["queue"];

    if(!a.IsArray()) {
      spdlog::get(LOFTILI_SPDLOG_ID)->warn("received invalid data format from api, queue did not appear as an array");
      return false;
    }

    while(!m_queue.empty()) m_queue.pop();

    for(rapidjson::SizeType i = 0; i < a.Size(); i++) {
      const rapidjson::Value& track = a[i];
      if(!track["streaming_url"].IsString()) continue;
      if(!track["id"].IsInt()) continue;
      std::string url = track["streaming_url"].GetString();
      int id = track["id"].GetInt();
      m_queue.push(std::make_pair(id, url));
      spdlog::get(LOFTILI_SPDLOG_ID)->info("found queue item: {0} [{1}]", url.c_str(), id);
    }

    if(m_queue.size() == 0) {
      spdlog::get(LOFTILI_SPDLOG_ID)->warn("queue appears to be empty, even after loading in new version");
      return false;
    }

    std::string first = std::get<1, int, std::string>(m_queue.front());
    int track_id = std::get<0, int, std::string>(m_queue.front());
    m_queue.pop();
    m_stateclient.Update("current_track", track_id);
    spdlog::get(LOFTILI_SPDLOG_ID)->info("sending first track into the audio player {0} [{1}]", first.c_str(), track_id);
    bool result = player.Play(first);

    if(result) {
      spdlog::get(LOFTILI_SPDLOG_ID)->info("player appeared to finish the track, popping from api");
      Pop();
    }

    return result;
  }

  return false;
}

const std::string Queue::QueueUrl() {
  std::stringstream ss;
  ss << loftili::api::configuration.protocol << "://";
  ss << loftili::api::configuration.hostname << ":" << loftili::api::configuration.port << "/queues/";
  ss << loftili::api::credentials.device_id;
  return ss.str();
}

}

}
