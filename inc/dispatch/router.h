#ifndef _LOFTILI_ROUTER_H
#define _LOFTILI_ROUTER_H

#include "route_list.h"
#include "controllers/root.h"
#include "controllers/player.h"

namespace loftili {

class Request;
class Response;

class Router {

  public:
    Router();
    ~Router();

    int handle(Request* req, Response* res);
    void initialize();

  private:
    RouteList* routes;

};
 

}

#endif
