#include "dispatch/route_list.h"

namespace loftili {

RouteList::RouteList() { 
}

RouteList::~RouteList() { }

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

  return controllers[1];
}

}
