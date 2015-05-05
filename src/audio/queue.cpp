#include "audio/queue.h"

namespace loftili {

namespace audio {

void Queue::Initialize(const loftili::api::DeviceCredentials& credentials){
  m_credentials = credentials;
};

void Queue::Pop() {
  std::string method = "POST";
  std::stringstream ss;
  ss << "/queues/" << m_credentials.device_id << "/pop";

  loftili::net::Request req(method, loftili::api::configuration.hostname, loftili::api::configuration.port, ss.str());
  req.Header(LOFTILI_API_TOKEN_HEADER, m_credentials.token);
  req.Header(LOFTILI_API_SERIAL_HEADER, loftili::api::configuration.serial);

  loftili::net::ResponseStream response_stream;
  int s = req.Send(&response_stream);
};

bool Queue::operator>>(loftili::audio::Player& player) {
  std::string method = "GET";
  std::stringstream ss;
  ss << "/queues/" << m_credentials.device_id;

  loftili::net::Request req(method, loftili::api::configuration.hostname, loftili::api::configuration.port, ss.str());
  req.Header(LOFTILI_API_TOKEN_HEADER, m_credentials.token);
  req.Header(LOFTILI_API_SERIAL_HEADER, loftili::api::configuration.serial);

  loftili::net::ResponseStream response_stream;
  int s = req.Send(&response_stream);

  if(response_stream.Count() != 1) return false;

  loftili::net::Response res;

  if(response_stream >> res && res.Code() >= 200 && res.Code() < 300) {
    rapidjson::Document document;
    document.Parse(res.Body().c_str());
    const rapidjson::Value& a = document["queue"];

    if(!a.IsArray()) return false;

    while(!m_queue.empty())
      m_queue.pop();

    for(rapidjson::SizeType i = 0; i < a.Size(); i++) {
      const rapidjson::Value& track = a[i];
      if(!track["streaming_url"].IsString()) continue;
      std::string url = track["streaming_url"].GetString();
      m_queue.push(url);
    }

    if(m_queue.size() == 0) return false;

    std::string first = m_queue.front();
    m_queue.pop();
    bool result = player.Play(first);

    if(result) Pop();

    return result;
  }

  return false;
}

}

}
