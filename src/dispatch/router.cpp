#include "dispatch/router.h"

namespace loftili {

Router::Router() {
  routes = new RouteList();
}

Router::~Router() {
  delete routes;
}

void Router::initialize() {
  routes->add(new RootController());
  routes->add(new PlayerController());
  routes->initialize();
}

int Router::handle(Request* req, Response* res) {
  Controller* c = routes->find(req);
  return c->respondTo(req, res);
}

}
