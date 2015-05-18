#include "audio/queue.h"

namespace loftili {

namespace audio {

void Queue::Initialize(const loftili::api::DeviceCredentials& credentials){
  m_credentials = credentials;
};

void Queue::Pop() {
  loftili::net::HttpClient client;
  std::string popurl = QueueUrl();
  popurl.append("/pop");
  loftili::net::HttpRequest req(loftili::net::Url(popurl.c_str()), "POST");
  req.Header(LOFTILI_API_TOKEN_HEADER, m_credentials.token);
  req.Header(LOFTILI_API_SERIAL_HEADER, loftili::api::configuration.serial);
  client.Send(req);
  return;
};

bool Queue::operator>>(loftili::audio::Player& player) {
  loftili::net::HttpClient client;
  loftili::net::HttpRequest req(loftili::net::Url(QueueUrl().c_str()));
  req.Header(LOFTILI_API_TOKEN_HEADER, m_credentials.token);
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
      std::string url = track["streaming_url"].GetString();
      m_queue.push(url);
    }

    if(m_queue.size() == 0) {
      spdlog::get(LOFTILI_SPDLOG_ID)->warn("queue appears to be empty, even after loading in new version");
      return false;
    }

    std::string first = m_queue.front();
    m_queue.pop();
    spdlog::get(LOFTILI_SPDLOG_ID)->info("sending first track into the audio player {0}", first.c_str());
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
  ss << "http://" << loftili::api::configuration.hostname;
  ss << ":1337/queues/";
  ss << m_credentials.device_id;
  return ss.str();
}

}

}
