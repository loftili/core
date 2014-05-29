#ifndef _RASBEAT_ROUTER_H
#define _RASBEAT_ROUTER_H

#include "communication/request.h"
#include "communication/response.h"

namespace rasbeat {

class Router {

  public:
    Router();
    ~Router();

    Response  handle(Request* request);

};
 

}

#endif
