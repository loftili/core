#include "util/registration.h"

namespace loftili {

Registration::Registration(Options opts) : log("registration") {
  options = opts;
}

bool Registration::attempt() {
  log.info("attempting to register...");
  Request req;
  Response* res = new Response("", 0);
  std::string api_host = options.api_host != "" ? options.api_host : LOFTILI_API_HOME;
  std::string registration_endpoint = "/registration";

  req.url = api_host + registration_endpoint;
  req.method = "POST";
  req.insert("username", options.username);
  req.insert("password", options.password);
  req.insert("devicename", options.devicename);
  req.insert("port", options.port);

  req.send(res);
  bool success = (res->status > 300 || res->status == NULL) ? false : true;
  delete res;
  return success;
}

}
