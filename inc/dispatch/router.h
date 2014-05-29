#ifndef _RASBEAT_ROUTER_H
#define _RASBEAT_ROUTER_H

#include "route_list.h"
#include "controllers/root.h"

namespace rasbeat {

class Request;
class Response;

class Router {

  public:
    Router();
    ~Router();

    Response* handle(Request* request);

  private:
    RouteList routes;

};
 

}

#endif
