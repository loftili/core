#include "dispatch/router.h"

namespace loftili {

Router::Router() {
  routes.add(new RootController());
  routes.add(new PlayerController());
}

Router::~Router() {
  routes.purge();
}

Response* Router::handle(Request* request) {
  Controller* c = routes.find(request);
  return c->respondTo(request);
}

}
