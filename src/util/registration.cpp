#include "util/registration.h"

namespace loftili {

Registration::Registration(Options opts) : log("registration") {
  options = opts;
}

bool Registration::attempt() {
  log.info("attempting to register...");
  Request r;
  std::string api_host = options.api_host != "" ? options.api_host : LOFTILI_API_HOME;
  std::string registration_endpoint = "/registration";

  r.url = api_host + registration_endpoint;
  r.method = "POST";
  r.insert("username", options.username);
  r.insert("password", options.password);
  r.insert("devicename", options.devicename);
  r.insert("port", options.port);

  long http_code = r.send();
  return (http_code > 300 || http_code == NULL) ? false : true;
}

}
