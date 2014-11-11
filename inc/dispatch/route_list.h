#ifndef _LOFTILI_ROUTE_LIST_H
#define _LOFTILI_ROUTE_LIST_H

#include <vector>
#include "auth/credentials.h"
#include "util/options.h"
#include "communication/request.h"
#include "controller.h"

namespace loftili {

class RouteList {

  public:
    RouteList();
    ~RouteList();
    
    void add(Controller* c);
    void purge();
    void initialize(Credentials creds, Options opts);
    Controller* find(Request* r);

  private:
    std::vector<Controller*> controllers;
    Logger* log;

};

}


#endif
