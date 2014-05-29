#include "dispatch/router.h"

namespace rasbeat {

Router::Router() {
  routes.add(new RootController());
}

Router::~Router() {
  routes.purge();
}

Response* Router::handle(Request* request) {
  Response* r;

  return r;
}

}
