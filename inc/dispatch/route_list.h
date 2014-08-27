#ifndef _LOFTILI_ROUTE_LIST_H
#define _LOFTILI_ROUTE_LIST_H

#include <vector>
#include "communication/request.h"
#include "controller.h"

namespace loftili {

class RouteList {

  public:
    RouteList();
    ~RouteList();
    
    void add(Controller* c);
    void purge();
    Controller* find(Request* r);

  private:
    std::vector<Controller*> controllers;
    Logger* log;

};

}


#endif
