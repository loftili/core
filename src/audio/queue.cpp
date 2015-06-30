#include "audio/queue.h"

namespace loftili {

namespace audio {

void Queue::Pop() {
  spdlog::get(LOFTILI_SPDLOG_ID)->info("queue is sending pop request");
  loftili::net::HttpClient client;
  std::string popurl = QueueUrl();
  popurl.append("/pop");
  loftili::net::HttpRequest req(loftili::net::Url(popurl.c_str()), "POST");
  req.Header(LOFTILI_API_TOKEN_HEADER, loftili::api::credentials.token);
  req.Header(LOFTILI_API_SERIAL_HEADER, loftili::api::configuration.serial);
  client.Send(req);
  spdlog::get(LOFTILI_SPDLOG_ID)->info("pop request finished");
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

    int queue_length = 0;
    int current_id = -1;

    for(rapidjson::SizeType i = 0; i < a.Size(); i++) {
      queue_length++;
      const rapidjson::Value& track = a[i];

      if(!track["id"].IsInt())
        continue;

      if(current_id < 0)
        current_id = track["id"].GetInt();
    }

    if(queue_length == 0 || current_id < 0) {
      spdlog::get(LOFTILI_SPDLOG_ID)->warn("queue appears to be empty, even after loading in new version");
      return false;
    }

    m_stateclient.Update("current_track", current_id);
    spdlog::get(LOFTILI_SPDLOG_ID)->info("updated current_track device state to id[{0}]", current_id);

    if(!player.Play()) return false;

    spdlog::get(LOFTILI_SPDLOG_ID)->info("player appeared to finish the track, popping from api");
    Pop();
    return true;
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
