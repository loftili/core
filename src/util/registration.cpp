#include "util/registration.h"

namespace loftili {

Registration::Registration(Options opts) : log("registration") {
  options = opts;
}

bool Registration::attempt() {
  log.info("attempting to register...");
  Request req;
  Json* req_json = new Json();
  Response* res = new Response("", 0);
  std::string api_host = options.api_host != "" ? options.api_host : LOFTILI_API_HOME;
  std::string registration_endpoint = "/registration";

  req.url = api_host + registration_endpoint;
  req.method = "POST";

  req_json->insert("username", options.username);
  req_json->insert("password", options.password);
  req_json->insert("devicename", options.devicename);
  req_json->insert("port", options.port);
  std::cout << req_json->buffer() << std::endl;

  req.send(req_json, res);
  bool success = (res->status > 300 || res->status == NULL) ? false : true;
  delete res;
  delete req_json;
  return success;
}

}
