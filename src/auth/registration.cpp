#include "auth/registration.h"

namespace loftili {

Registration::Registration(Options opts) : log("registration"), current_credentials() {
  options = opts;
}

std::string Registration::endpoint() {
  std::stringstream ss;
  ss << (options.api_host != "" ? options.api_host : LOFTILI_API_HOME) << "/registration";
  return ss.str();
}

Credentials Registration::creds() {
  return current_credentials;
}

Options Registration::opts() {
  return options;
}

bool Registration::attempt() {
  log.info("attempting to register...");
  Request req;
  Json* req_json = new Json();

  Response* res = new Response("", 0);
    
  req.url = endpoint();
  req.method = "POST";

  req_json->insert("username", options.username);
  req_json->insert("password", options.password);
  req_json->insert("devicename", options.devicename);
  req_json->insert("port", options.port);

  req.send(req_json, res);

  bool success = (res->status > 300 || res->status == NULL) ? false : true;

  delete req_json;

  if(!success)
    return false;

  rapidjson::Document registration_doc;
  registration_doc.Parse<0>((char*) res->content);

  if(!registration_doc["token"].IsString() || !registration_doc["id"].IsNumber())
    return false;

  std::string token = registration_doc["token"].GetString();
  int device_id = (int) registration_doc["id"].GetInt();

  current_credentials.initialize(token, device_id);
  return current_credentials.valid();
}

}
