#include "../inc/router.h"

namespace rasbeat {

Router::Router() {
}

Router::~Router() {
}

Response Router::handle(Request* request) {
  Response r;

  if(request->url == "/favicon.ico")
    r.status = 404;

  return r;
}

}
