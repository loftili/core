#include "services/registration.h"

namespace loftili {

RegistrationService::RegistrationService() {
}

RegistrationService::~RegistrationService() {
}

bool RegistrationService::authenticate(Configuration* config) {
  Logger log("RegistrationService");

  bool validated;

  string endpoint;

  if(config->api_host != "")
    endpoint = config->api_host + LOFTILI_REGISTRATION_PATH;
  else
    endpoint = LOFTILI_REGISTRATION_URL;

  log.info("preparing data packet, sending to url: ", endpoint);
  log.info(" - username: ", config->username);
  log.info(" - devicename: ", config->devicename);

  Request req;
  Json* req_json = new Json();

  Response* res = new Response("", 0);
    
  req.url = endpoint;
  req.method = "POST";

  req_json->insert("username", config->username);
  req_json->insert("password", config->password);
  req_json->insert("devicename", config->devicename);
  req_json->insert("port", config->port);

  req.send(req_json, res);

  bool success = (res->status > 300 || res->status == NULL) ? false : true;

  delete req_json;

  if(!success) {
    log.info("server returned invalid response");
    delete res;
    return false;
  }

  rapidjson::Document registration_doc;
  registration_doc.Parse<0>((char*) res->content);

  if(!registration_doc["token"].IsString() || !registration_doc["id"].IsNumber()) {
    delete res;
    return false;
  }

  std::string token = registration_doc["token"].GetString();
  int device_id = (int) registration_doc["id"].GetInt();

  config->token = token;
  config->device_id = device_id;

  delete res;

  return device_id >= 0;
}

}
