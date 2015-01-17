#include "services/state_relay.h"

namespace loftili {

StateRelay::StateRelay() {
  log = new Logger("StateRelay");
}

StateRelay::~StateRelay() {
  delete log;
}

void StateRelay::send(string key, int state) {
  stringstream update_log;
  update_log << "sending updated state for key:" << key;
  update_log << "changing value to: " << state;
  log->info(update_log.str());

  Request req;
  Response* res = new Response("", 0);

  stringstream endpoint;

  if(loftili::config->api_host != "")
    endpoint << loftili::config->api_host;
  else
    endpoint << LOFTILI_API_HOME;

  endpoint << "/devicestates/" << loftili::config->device_id;
  endpoint << "?device_token=" << loftili::config->token;

  log->info("sending put to", endpoint.str());

  req.url = endpoint.str();
  req.method = "PUT";

  Json* req_json = new Json();

  req_json->insert(key, state);

  req.send(req_json, res);

  bool success = (res->status > 300 || res->status == NULL) ? false : true;

  delete req_json;

  if(!success) {
    log->info("unable to PUT the new states");
  } else {
    log->info("successfully updated states");
  }

  delete res;
  return;
}

}
