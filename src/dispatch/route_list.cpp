#include "dispatch/route_list.h"

namespace loftili {

RouteList::RouteList() { 
  log = new Logger("Route list");
}

RouteList::~RouteList() {
  purge();
  delete log;
}

void RouteList::add(Controller* controller) {
  controllers.push_back(controller);
}

void RouteList::initialize(Credentials creds, Options opts) {
  auto it = controllers.begin();
  log->info("initalizing controllers");

  for(it; it != controllers.end(); ++it) {
    Controller* c = (Controller*) *it;
    c->initialize(creds, opts);
  }
}

void RouteList::purge() {
  log->info("deleting controllers");
  for(int i = 0; i < controllers.size(); i++) {
    delete controllers[i];
  }
  controllers.clear();
}

Controller* RouteList::find(Request* request) {
  log->info("searching route list for matching controller");

  for(auto it = controllers.begin(); it != controllers.end(); ++it) {
    Controller* c = (Controller*)*it;
    log->info(std::string("found controller: ") + c->logName());

    for(auto method = c->method_map.begin(); method != c->method_map.end(); ++method) {
      log->info(std::string("found method: ") + method->first);
      if(method->first == request->url) {
        request->c_method = method->second;
        return c;
      }
    }
  }
    
  request->c_method = CONTROLLER_METHOD_MISSING;
  return controllers[0];
}

}
