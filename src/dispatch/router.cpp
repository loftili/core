#include "dispatch/router.h"

namespace loftili {

Router::Router() {
  routes = new RouteList();
}

Router::~Router() {
  delete routes;
}

void Router::initialize(Credentials creds, Options opts) {
  routes->add(new RootController());
  routes->add(new PlayerController());
  routes->initialize(creds, opts);
}

int Router::handle(Request* req, Response* res) {
  Controller* c = routes->find(req);
  return c->respondTo(req, res);
}

}
