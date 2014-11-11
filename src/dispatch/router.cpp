#include "dispatch/router.h"

namespace loftili {

Router::Router() {
  routes.add(new RootController());
  routes.add(new PlayerController());
}

Router::~Router() {
  routes.purge();
}

void Router::initialize(Credentials creds, Options opts) {
  routes.initialize(creds, opts);
}

int Router::handle(Request* req, Response* res) {
  Controller* c = routes.find(req);
  return c->respondTo(req, res);
}

}
