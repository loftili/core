#include "dispatch/route_list.h"

namespace loftili {

RouteList::RouteList() { 
  log = new Logger("Route list");
}

RouteList::~RouteList() { 
  delete log;
}

void RouteList::add(Controller* controller) {
  controller->initialize();
  controllers.push_back(controller);
}

void RouteList::purge() {
  auto it = controllers.begin();
  for(it; it != controllers.end(); ) {
    Controller* c = (Controller*)*it;
    delete c;
    controllers.erase(it);
  }
}

Controller* RouteList::find(Request* request) {
  if(request->url == "/favicon.ico")
    return controllers[0];

  log->info("Searching route list for matching controller");
  for(auto it = controllers.begin(); it != controllers.end(); ++it) {
    Controller* c = (Controller*)*it;
    log->info(std::string("Found controller: ") + c->logName());
    for(auto method = c->method_map.begin(); method != c->method_map.end(); ++method) {
        log->info(std::string("Found method: ") + method->first);
        if(method->first == request->url) {
          request->c_method = method->second;
          return c;
        }
    }
  }

  request->c_method = -1;
  return controllers[0];
}

}
