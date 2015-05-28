#include "api/state_client.h"

namespace loftili {

namespace api {


void StateClient::Update(std::string key, int val) {
  loftili::net::HttpClient client;

  std::stringstream body;
  body << "{";
  body << "\"" << key << "\": \"" << val << "\"";
  body << "}";

  spdlog::get(LOFTILI_SPDLOG_ID)->info("attempting to update {0} in the device state to {1}", key, val);
  loftili::net::HttpRequest req(loftili::net::Url(StateUrl().c_str()), "PUT", body.str());
  req.Header(LOFTILI_API_TOKEN_HEADER, loftili::api::credentials.token);
  req.Header(LOFTILI_API_SERIAL_HEADER, loftili::api::configuration.serial);

  if(!client.Send(req) || client.Latest()->Status() != 200) {
    spdlog::get(LOFTILI_SPDLOG_ID)->warn("unable to update device state!");
    return;
  }

  spdlog::get(LOFTILI_SPDLOG_ID)->info("successfully updated state");
}

std::string StateClient::StateUrl() {
  std::stringstream ss;
  ss << loftili::api::configuration.protocol << "://";
  ss << loftili::api::configuration.hostname << ":" << loftili::api::configuration.port << "/devicestates/";
  ss << loftili::api::credentials.device_id;
  return ss.str();
}

}

}
