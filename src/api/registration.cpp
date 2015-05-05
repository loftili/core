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

int Registration::Register() {
  std::string hostname = loftili::api::configuration.hostname;
  int port = loftili::api::configuration.port;

  loftili::net::ResponseStream stream;
  loftili::net::Request req("POST", hostname, port, "/registration");
  req.Header("Content-Type", "application/json");

  std::stringstream body;
  body << "{";
  body << "\"serial_number\": \"" << loftili::api::configuration.serial << "\"";
  body << "}";

  req.Send(&stream, body.str());

  if(stream.Count() != 1) return -1;

  loftili::net::Response res;

  if(stream >> res && res.Code() >= 200 && res.Code() < 300) {
    loftili::api::JsonStream ss(res.Body().c_str());
    rapidjson::Reader reader;
    loftili::api::Registration::Parser p(this);
    reader.Parse<0, loftili::api::JsonStream, loftili::api::Registration::Parser>(ss, p);
  }

  return m_credentials.token.size() > 0 && m_credentials.device_id > 0 ? 1 : 0;
};

}

}
