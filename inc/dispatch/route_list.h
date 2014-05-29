#ifndef _RASBEAT_ROUTE_LIST_H
#define _RASBEAT_ROUTE_LIST_H

#include <vector>
#include "controller.h"

namespace rasbeat {

class RouteList {

public:
  RouteList();
  ~RouteList();
  
  void add(Controller* c);
  void purge();

private:
  std::vector<Controller*> controllers;


};

}


#endif
