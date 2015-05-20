#include "api/registration.h"

namespace loftili {

namespace api {

loftili::api::DeviceCredentials Registration::Credentials() {
  return m_credentials;
};

Registration::Parser::Parser(Registration* ptr) {
  m_registration = ptr;
};

bool Registration::Parser::Uint(unsigned int value) {
  if(m_current_key == "device")
    m_registration->m_credentials.device_id = value;

  return true;
};

bool Registration::Parser::String(const char* value, size_t, bool) {
  if(m_current_key == "token")
    m_registration->m_credentials.token = std::string(value);

  return true;
};

bool Registration::Parser::Key(const char* value, size_t, bool) {
  m_current_key = value;
  return true;
};

std::string Registration::RegistrationUrl() {
  std::stringstream url;
  url << "http://" << loftili::api::configuration.hostname << ":1337/registration";
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

  if(client.Send(req)) {
    spdlog::get(LOFTILI_SPDLOG_ID)->info("request finished, checking result...");
    std::shared_ptr<loftili::net::HttpResponse> res = client.Latest();
    if(res->Status() < 200 || res->Status() > 299) return 0;
    loftili::api::JsonStream ss(res->Body());
    rapidjson::Reader reader;
    loftili::api::Registration::Parser p(this);
    reader.Parse<0, loftili::api::JsonStream, loftili::api::Registration::Parser>(ss, p);
    spdlog::get(LOFTILI_SPDLOG_ID)->info("registration attempt complete");
  }

  if(m_credentials.token.size() < 1)
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("registration attempt failed, unable to retrieve a valid api token");


  return m_credentials.token.size() > 0 && m_credentials.device_id > 0 ? 1 : 0;
};

}

}
