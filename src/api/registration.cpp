#include "api/registration.h"

namespace loftili {

namespace api {

bool Registration::Parser::Uint(unsigned int value) {
  if(m_current_key == "device")
    loftili::api::credentials.device_id = value;

  return true;
};

bool Registration::Parser::String(const char* value, size_t, bool) {
  if(m_current_key == "token")
    loftili::api::credentials.token = std::string(value);

  return true;
};

bool Registration::Parser::Key(const char* value, size_t, bool) {
  m_current_key = value;
  return true;
};

std::string Registration::RegistrationUrl() {
  std::stringstream url;
  url << loftili::api::configuration.protocol << "://";
  url << loftili::api::configuration.hostname << ":" << loftili::api::configuration.port << "/registration";
  return url.str();
}

int Registration::Register() {
  loftili::net::HttpClient client;
  std::stringstream body;
  body << "{";
  body << "\"serial_number\": \"" << loftili::api::configuration.serial << "\"";
  body << "}";
  loftili::net::HttpRequest req(loftili::net::Url(RegistrationUrl().c_str()), "POST", body.str());
  spdlog::get(LOFTILI_SPDLOG_ID)->info("registering serial number {0}", loftili::api::configuration.serial);

  std::shared_ptr<loftili::net::HttpResponse> res;

  if(!client.Send(req) || (res = client.Latest())->Status() != 200) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("unable to send registration request to api.");
    return 0;
  }

  loftili::api::JsonStream ss(res->Body());
  rapidjson::Reader reader;
  loftili::api::Registration::Parser p;
  reader.Parse<0, loftili::api::JsonStream, loftili::api::Registration::Parser>(ss, p);
  spdlog::get(LOFTILI_SPDLOG_ID)->info("registration attempt complete");

  if(loftili::api::credentials.token.size() < 1)
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("registration attempt failed, unable to retrieve a valid api token");
  else
    spdlog::get(LOFTILI_SPDLOG_ID)->info("received token from server: {0}", loftili::api::credentials.token.c_str());


  return loftili::api::credentials.token.size() > 0 && loftili::api::credentials.device_id > 0 ? 1 : 0;
};

}

}
